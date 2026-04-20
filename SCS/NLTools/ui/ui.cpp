#include <ftxui/component/app.hpp>
#include "ui.h"
#include "../include/exec.h"
#include "../include/llm_service.h"
#include "../include/config.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"

void TUI::modeToggle(){
  
}

void TUI::buttonEvent(){
  // 代码参考 https://arthursonzogni.github.io/FTXUI/examples_2component_2button_animated_8cpp-example.html
  bool buttonPushed = false;
  auto buttons = ftxui::Container::Horizontal({
    Button(
        "生成", [&] { TUI::genButtonEvent(buttonPushed); }, ftxui::ButtonOption::Animated(ftxui::Color::Red)),
    Button(
        "切换模式", [&] { TUI::modeToggle(); }, ftxui::ButtonOption::Animated(ftxui::Color::Green)),
    Button(
        "拒绝执行", [&] {/*拒绝执行相关逻辑*/ }, ftxui::ButtonOption::Animated(ftxui::Color::Blue)),
  });
}

void TUI::genButtonEvent(bool buttonPushed){
  if (!buttonPushed){
    /*生成prompt*/
    int mode = TUI::getMode();
    std::string input = TUI::getUsrInput();
    std::string inputFile = TUI::getInputFile();
    std::string outputFile = TUI::getOutputFile();
    std::string outputDir = TUI::getOutputDir();

    //加载配置
    llmConfig config = llmConfig::load("config.json");

    // 获取LLM配置
    std::string api_key = config.get_api_key();
    std::string model_endpoint = config.get_model_endpoint();
    std::string model_name = config.get_model_name();
    if (api_key.empty() || model_endpoint.empty() || model_name.empty()){
      std::cerr << "Error: Config Not Set properly, plz fill all blanks in config.json" << std::endl;
    }

    std::string prompt = LLMService::generatePrompt(input, mode, inputFile, outputFile, outputDir);
    std::string request = LLMService::sendRequest(prompt, api_key, model_endpoint, model_name);
    std::string cmd = cmdExec::generateCmd(request);
  }
  else if (buttonPushed) {
    /*执行prompt*/
  }
}

std::string getCmdFeedBack(){
  int mode = TUI::getMode();
  std::string input = TUI::getUsrInput();
  std::string inputFile = TUI::getInputFile();
  std::string outputFile = TUI::getOutputFile();
  std::string outputDir = TUI::getOutputDir();

  //加载配置
  llmConfig config = llmConfig::load("config.json");
  
  // 获取LLM配置
  std::string api_key = config.get_api_key();
  std::string model_endpoint = config.get_model_endpoint();
  std::string model_name = config.get_model_name();
  if (api_key.empty() || model_endpoint.empty() || model_name.empty()){
    std::cerr << "Error: Config Not Set properly, plz fill all blanks in config.json" << std::endl;
  }
  
  std::string prompt = LLMService::generatePrompt(input, mode, inputFile, outputFile, outputDir);
  std::string request = LLMService::sendRequest(prompt, api_key, model_endpoint, model_name);
  std::string cmd = cmdExec::generateCmd(request);

  return cmd;
}

int TUI::getMode(){
  return mode;
}

// 获取自然语言输入
std::string TUI::getUsrInput(){
  // 代码参考 https://arthursonzogni.github.io/FTXUI/examples_2component_2input_8cpp-example.html
  std::string input;
  ftxui::Component inputBlock = ftxui::Input(&input, "How you wanna do with this file?");
  return input;
}

// 获取输出文件名称
std::string getOutputFile(){
  std::string fileName;
  ftxui::Component inputBlock = ftxui::Input(&fileName, "The Output File Name");
  return fileName;
}

void TUI::execCmd(std::string& cmd){
  if (!cmd.empty() && cmdExec::isSafe(cmd)){
    // TODO: 生成按钮显示为确认执行
    // TODO: 按下按钮1
    cmdExec::exec(cmd);
  }else{
    delCmd(cmd);
    // TODO: TUI报错逻辑
    std::cerr << "Not A Safe Command" << std::endl;
  }
}

void TUI::delCmd(std::string& cmd){
  cmd = nullptr;
}
