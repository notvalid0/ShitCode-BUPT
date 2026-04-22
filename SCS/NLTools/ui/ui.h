#pragma once
#include <iostream>

class TUI {
private:
  int mode = 0; // 默认为FFMpeg
public:
  TUI();
  void showTUI();

  void modeToggle(); // 选择MODE(0 for FFMpeg, 1 for Pandoc)
  void buttonEvent();

  void genButtonEvent(bool buttonPushed); // 关于第一个按钮的设置

  int getMode() { return mode; };
  static std::string getInputFile();
  static std::string getOutputDir();
  static std::string getOutputFile();
  static std::string getUsrInput();

  bool wannaExec = false;
  void execCmd(std::string &cmd);
  void delCmd(std::string &cmd);
};
