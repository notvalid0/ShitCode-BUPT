// 关于如何接入LLM,harness参考https://learn.shareai.run/zh/
// 读取配置部分参考https://blog.csdn.net/u014248312/article/details/107596301

// LLM设置 && 读取配置(已从设想.env格式改用json格式config)
#pragma once
#include <string>

class llmConfig {
private:
  std::string model_endpoint;
  std::string api_key;
  std::string model_name;

public:
  // 从config.env读取配置
  static llmConfig load(const std::string &config_file);
  // Getters
  std::string get_model_endpoint() const;
  std::string get_api_key() const;
  std::string get_model_name() const;
};
