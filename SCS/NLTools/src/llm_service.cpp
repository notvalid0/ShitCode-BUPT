#include "../include/llm_service.h"
#include <curl/curl.h> //请求LLM
#include <curl/easy.h>
#include <nlohmann/json.hpp>
#include <string>

//mode 0: FFmpeg mode1: pandoc
std::string LLMService::generatePrompt(const std::string &input,
                                       const int &mode,
                                       const std::string &inputFile,
                                       const std::string &outputFile, const std::string &outputDir) {
  std::string tool = (mode == 0) ? "ffmpeg" : "pandoc";
  std::string prompt = "你是一个" + tool +
                       "专家。请将用户的自然语言描述转换为" + tool +
                       "命令行命令。\n"
                       "\n"
                       "要求:\n"
                       "1. 只返回 JSON 格式响应\n"
                       "2. JSON 格式必须为:{\"tool\": \"" +
                       tool +
                       "\", \"command\": \"完整命令\"}\n"
                       "3. 不要包含任何解释，只返回 JSON\n"
                       "4. 确保命令安全且可执行\n"
                       "\n"
                       "输入文件：" +
                       inputFile +
                       "\n"
                       "输出文件：" +
                       outputDir + "/" + outputFile +
                       "\n"
                       "用户需求：" +
                       input +
                       "\n"
                       "\n"
                       "请**输出且仅输出** JSON 格式的响应，不要包含任何解释。";
  return prompt;
}

// 发送请求的静态成员函数
std::string LLMService::sendRequest(const std::string &prompt,
                                     const std::string &api_key,
                                     const std::string &model_endpoint,
                                     const std::string &model_name) {
  // TODO: 通过CURL发送请求
  CURL *c = curl_easy_init();
  std::string r;
  auto j =
      nlohmann::json{{"model", model_name},
                     {"messages", {{{"role", "user"}, {"content", prompt}}}},
                     {"stream", false}};
  struct curl_slist *h = nullptr;
  h = curl_slist_append(h, ("Authorization: Bearer " + api_key).c_str());
  h = curl_slist_append(h, "Content-Type: application/json");
  curl_easy_setopt(c, CURLOPT_URL,
                   model_endpoint.c_str()); // 函数只能使用char作为input
  
  //参考https://www.cnblogs.com/linuxAndMcu/p/14503341.html
  std::string json_str = j.dump();
  // 第一次检修结果->j.dump()返回临时对象，需要储存防止丢失
  curl_easy_setopt(c, CURLOPT_POSTFIELDS, json_str.c_str());
  
  curl_easy_setopt(c, CURLOPT_HTTPHEADER, h);
  curl_easy_setopt(
      c, CURLOPT_WRITEFUNCTION,
      +[](char *p, size_t s, size_t n, std::string *r) {
        r->append(p, s * n);
        return s * n;
      });
  curl_easy_setopt(c, CURLOPT_WRITEDATA, &r);
  CURLcode res = curl_easy_perform(c);
  curl_easy_cleanup(c);
  curl_slist_free_all(h);
  
  // 检查CURL请求是否成功
  if (res != CURLE_OK) {
    return ""; // 返回空字符串表示错误
  }
  
  // 尝试解析JSON响应
  try {
    nlohmann::json response = nlohmann::json::parse(r);
    // 检查响应是否包含必要的字段
    if (response.contains("choices") && response["choices"].is_array() && 
        !response["choices"].empty() && response["choices"][0].contains("message") &&
        response["choices"][0]["message"].contains("content")) {
      return response["choices"][0]["message"]["content"].get<std::string>();
    }
    return ""; // 返回空字符串表示响应格式不正确
  } catch (const nlohmann::json::exception& e) {
    // JSON解析失败，返回空字符串
    return "";
  }
}
