// 分析JSON(需改进), 判断是否安全, 执行指令

#pragma once
#include <string>

class cmdExec {
public:
  static std::string generateCmd(const std::string &jsonFeedback); // 解析JSON
  static bool isSafe(const std::string &cmd); // 判断指令鲁棒性
  static int exec(const std::string &cmd);    // 执行指令, 需要返回-1因此是int
};
