#include "ui.h"

#include "../include/config.h"
#include "../include/exec.h"
#include "../include/llm_service.h"

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>

#include <thread>

TUI::TUI()
    : screen_(ftxui::ScreenInteractive::Fullscreen()),
      root_component_(nullptr) {}

TUI::~TUI() = default;

void TUI::run() {
  root_component_ = buildUI();
  screen_.Loop(root_component_);
}

ftxui::Component TUI::buildUI() {
  using namespace ftxui;

  // 组件
  nl_input_ = Input(&state_.nlDesc);
  in_file_ = Input(&state_.inputFile);
  out_file_ = Input(&state_.outputFile);
  out_dir_ = Input(&state_.outputDir);

  mode_toggle_ = Toggle(&modes_, &state_.mode);

  // TODO: Generate Buttons
  // Button Logic
  // 参考https://arthursonzogni.github.io/FTXUI/examples_2component_2button_animated_8cpp-example.html
  btn_gen_ = Button(
      " 生成命令 ", [this] { onGenerate(); },
      ButtonOption::Animated(Color::Yellow));

  btn_exe_ = Button(
      " 执行 ", [this] { onExecute(); },
      ButtonOption::Animated(Color::GreenLight));

  btn_clr_ = Button(
      " 清空 ", [this] { onClear(); }, ButtonOption::Animated(Color::RedLight));

  button_bar_ = Container::Horizontal({btn_gen_, btn_exe_, btn_clr_});

  main_container_ = Container::Vertical({
      mode_toggle_,
      nl_input_,
      in_file_,
      out_file_,
      out_dir_,
      button_bar_,
  });

  // TODO: Renderer
  auto renderer = Renderer(main_container_, [this] {
    auto ffmpeg_style = (state_.mode == 0) ? (color(Color::Green) | bold) : dim;
    auto pandoc_style = (state_.mode == 1) ? (color(Color::Cyan) | bold) : dim;

    auto status_color = Color::White;
    if (state_.isProcessing)
      status_color = Color::Yellow;
    else if (state_.statusMsg.find("成功") != std::string::npos)
      status_color = Color::Green;
    else if (state_.statusMsg.find("错误") != std::string::npos ||
             state_.statusMsg.find("失败") != std::string::npos)
      status_color = Color::Red;

    // 主体框架，参考官方box示例
    return vbox({
        text(" NLTools — 自然语言命令行工具 ") | bold | center,
        separator(),
        hbox({
            text(" 工具: "),
            text(" FFmpeg ") | ffmpeg_style,
            text("  "),
            text(" Pandoc ") | pandoc_style,
        }),
        separatorEmpty(),
        hbox({
            text(" 模式切换: "),
            mode_toggle_->Render() | border,
        }),
        separatorEmpty(),
        hbox({
            text(" 需求:     "),
            nl_input_->Render() | border | flex,
        }),
        separatorEmpty(),
        hbox({
            text(" 输入文件: "),
            in_file_->Render() | border | flex,
        }),
        separatorEmpty(),
        hbox({
            text(" 输出文件: "),
            out_file_->Render() | border | flex,
        }),
        separatorEmpty(),
        hbox({
            text(" 输出目录: "),
            out_dir_->Render() | border | flex,
        }),
        separatorEmpty(),
        hbox({
            btn_gen_->Render(),
            separatorEmpty(),
            btn_exe_->Render(),
            separatorEmpty(),
            btn_clr_->Render(),
        }) | center,
        separator(),
        hbox({
            text(" 生成命令: "),
            text(state_.generatedCmd.empty() ? "(尚未生成)"
                                             : state_.generatedCmd) |
                color(Color::YellowLight),
        }),
        hbox({
            text(" 状态: "),
            text(state_.statusMsg) | color(status_color),
        }),
    });
  });

  return renderer;
}

void TUI::onGenerate() {
  if (state_.isProcessing)
    return;
  if (state_.nlDesc.empty()) {
    state_.statusMsg = "错误: 请输入自然语言描述";
    return;
  }

  state_.isProcessing = true;
  state_.statusMsg = "正在调用 LLM 生成命令...";
  state_.hasGenerated = false;
  state_.generatedCmd.clear();

  int mode = state_.mode;
  std::string nlDesc = state_.nlDesc;
  std::string inputFile = state_.inputFile;
  std::string outputFile = state_.outputFile;
  std::string outputDir = state_.outputDir;

  auto *screen_ptr = &screen_;

  std::thread([this, screen_ptr, mode, nlDesc, inputFile, outputFile,
               outputDir]() {
    llmConfig config = llmConfig::load("config.json");
    std::string api_key = config.get_api_key();
    std::string model_endpoint = config.get_model_endpoint();
    std::string model_name = config.get_model_name();

    if (api_key.empty() || model_endpoint.empty() || model_name.empty()) {
      screen_ptr->Post([this] {
        state_.isProcessing = false;
        state_.statusMsg = "错误: config.json 配置不完整";
      });
      return;
    }

    std::string prompt = LLMService::generatePrompt(nlDesc, mode, inputFile,
                                                    outputFile, outputDir);
    std::string request =
        LLMService::sendRequest(prompt, api_key, model_endpoint, model_name);

    if (request.empty()) {
      screen_ptr->Post([this] {
        state_.isProcessing = false;
        state_.statusMsg =
            "错误: LLM 请求失败或返回为空（请检查网络与 API Key）";
      });
      return;
    }

    std::string cmd = cmdExec::generateCmd(request);

    screen_ptr->Post([this, cmd] {
      state_.generatedCmd = cmd;
      state_.hasGenerated = true;
      state_.isProcessing = false;
      state_.statusMsg = "指令已生成，请检查后执行";
    });
  }).detach();
}

void TUI::onExecute() {
  if (!state_.hasGenerated || state_.generatedCmd.empty()) {
    state_.statusMsg = "请先生成命令";
    return;
  }
  if (!cmdExec::isSafe(state_.generatedCmd)) {
    state_.statusMsg = "安全性检查未通过，拒绝执行";
    state_.hasGenerated = false;
    return;
  }

  state_.isProcessing = true;
  state_.statusMsg = "正在执行...";
  std::string cmd = state_.generatedCmd;
  auto *screen_ptr = &screen_;

  std::thread([this, screen_ptr, cmd]() {
    int ret = cmdExec::exec(cmd);
    screen_ptr->Post([this, ret] {
      state_.isProcessing = false;
      state_.hasGenerated = false;
      state_.statusMsg = (ret == 0)
                             ? "执行成功"
                             : "执行失败 (返回码: " + std::to_string(ret) + ")";
    });
  }).detach();
}

void TUI::onClear() { state_ = State{}; }
