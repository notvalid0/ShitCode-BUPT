// 设定prompt, 获取json, 发送请求(参考LongCat文档，暂定使用CURL)， 获取Cmd

#pragma once
#include <string>

class LLMService {
public:
  // 此部分应当参考https://longcat.chat/platform/docs/ CURL部分请求部分
  // 参考https://www.cnblogs.com/ow-dwh/p/17153582.html
  static std::string generatePrompt(const std::string &input, const int &mode,
                 const std::string &inputFile,
                 const std::string &outputFile, const std::string &outputDir); // 需要依据输入生成Prompt

  // 发送curl请求，(如果可以)直接返回输string
  static std::string sendRequest(const std::string &prompt,
                                 const std::string &api_key,
                                 const std::string &model_endpoint,
                                 const std::string &model_name);
};
