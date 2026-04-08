// 基本实现流程: 读取用户输入(UI) -> 获取llm config(config) -> 发送请求获取LLM
// feedback(llm_service)) -> 判断、解析、执行(exec)

#include "include/config.h"
#include "include/exec.h"
#include "include/llm_service.h"

#include <string>
#include <iostream>

int main() {
  // 加载配置
  llmConfig config = llmConfig::load("config.json");

  // 获取LLM配置
  std::string api_key = config.get_api_key();
  std::string model_endpoint = config.get_model_endpoint();
  std::string model_name = config.get_model_name();

  if (api_key.empty() || model_endpoint.empty() || model_name.empty()){
    std::cerr << "Error: Config Not Set properly, plz fill all blanks in config.json" << std::endl;
  }

  //Later TODO: UI

  int mode;
  std::cout << "plz input mode :(0 for ffmpeg, 1 for pandoc)" <<std::endl;
  std::cin >> mode;

  std::string input;
  std::cout << "plz input Natural Language about how you wanna to do with this file" <<std::endl;
  std::cin >> input;

  std::string inputFile;
  std::cout << "where's the input File?" <<std::endl;
  std::cin >> inputFile;

  std::string outputFile;
  std::cout << "what about the outputFile?" <<std::endl;
  std::cin >> outputFile;

  std::string prompt = LLMService::generatePrompt(input,mode,inputFile,outputFile);
  std::string request = LLMService::sendRequest(prompt, api_key, model_endpoint,model_name);
  std::string cmd = cmdExec::generateCmd(request);
  std::cout << "output: " << cmd << std::endl;

  char c;
  std::cout << "Execute? (Y/n)" << std::endl;
  std::cin >>c;
  if(c == 'Y' || c == 'y'){
    if (cmdExec::isSafe(cmd)) {
      cmdExec::exec(cmd);
    }
    else {
    std::cout << "Not a SAFE command" << std::endl;
    }
  }
  
  return 0;
}
