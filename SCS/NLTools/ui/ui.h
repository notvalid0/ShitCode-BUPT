#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

#include <string>
#include <vector>

class TUI {
public:
  TUI();
  ~TUI();
  void run();

private:
  struct State {
    int mode = 0;
    std::string nlDesc;
    std::string inputFile;
    std::string outputFile;
    std::string outputDir = ".";
    std::string generatedCmd;
    std::string statusMsg = "就绪 — 请输入需求后点击「生成命令」";
    bool isProcessing = false;
    bool hasGenerated = false;
  };
  State state_;

  const std::vector<std::string> modes_ = {"FFmpeg", "Pandoc"};

  // Components
  ftxui::Component nl_input_;
  ftxui::Component in_file_;
  ftxui::Component out_file_;
  ftxui::Component out_dir_;
  ftxui::Component btn_gen_;
  ftxui::Component btn_exe_;
  ftxui::Component btn_clr_;
  ftxui::Component mode_toggle_;
  ftxui::Component button_bar_;
  ftxui::Component main_container_;
  ftxui::Component root_component_;
  ftxui::ScreenInteractive screen_;

  ftxui::Component buildUI();

  void onGenerate();
  void onExecute();
  void onClear();
};
