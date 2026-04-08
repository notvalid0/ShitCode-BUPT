#include "../include/config.h"
#include <fstream> // 读取配置文件
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

// 参考https://blog.csdn.net/u014248312/article/details/107596301
// 要求必须已经写完配置
llmConfig llmConfig::load(const std::string &config_file) {
  llmConfig llm_config;

  // 使用JSON便于调用现有函数进行操作
	json j;			// 创建 json 对象
	std::ifstream jfile("config.json");
	jfile >> j;		// 以文件流形式读取 json 文件
	llm_config.model_endpoint = j.at("model_endpoint");
	llm_config.api_key = j.at("api_key");
	llm_config.model_name = j.at("model_name");
	
  return llm_config;
}

std::string llmConfig::get_api_key() const { return api_key; }
std::string llmConfig::get_model_endpoint() const { return model_endpoint; }
std::string llmConfig::get_model_name() const { return model_name; }
