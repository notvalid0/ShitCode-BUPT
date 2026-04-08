#include "../include/exec.h"
#include <iostream>
#include <nlohmann/json.hpp> //使用JSON库便于操作

using json = nlohmann::json;

std::string cmdExec::generateCmd(const std::string &jsonFeedback) {
  // TODO: 学习nlohmann::json库, 尝试转换LLM输出的JSON
  // 参考： https://www.cnblogs.com/linuxAndMcu/p/14503341.html#_label2_3
  // 鲁棒性有待考究...
  json j = json::parse(jsonFeedback);
  return j["command"];
}

bool cmdExec::isSafe(const std::string &cmd) {
  // TODO: 判断命令是否安全
  // 尝试通过判断(我认为)危险字符串是否为子串来判断
  std::vector<std::string> dangerous_patterns = {"rm -rf", "sudo", "mkfs",
                                                 "rm"};
  // 参考https://www.php.cn/faq/1625457.html
  for (const auto &pattern : dangerous_patterns) {
    if (cmd.find(pattern) != std::string::npos) {
      return false;
    }
  }
  return true;
}

int cmdExec::exec(const std::string &cmd) {
  // 不安全 -> 不执行
  if (!isSafe(cmd)) {
    std::cerr << "Unsafe CMD"<< std::endl; // 输出错误信息
    return -1;
  }

  std::cout << "Executing command: " << cmd << std::endl; // 输出执行信息

  return system(cmd.c_str()); // 执行命令
}
