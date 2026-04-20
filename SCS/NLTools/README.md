# NLTools

基于LLM的自然语言命令行工具转换软件

[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![C++ Standard](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/)
[![CMake](https://img.shields.io/badge/CMake-4.0%2B-orange.svg)](https://cmake.org/)

## 项目简介

NLTools 是一个基于大语言模型(LLM)的命令行工具转换软件，能够将用户的自然语言描述转换为 FFmpeg 或 Pandoc 命令并执行。用户只需以自然语言描述需求，即可自动生成对应的命令行指令。

## 功能特性

- **自然语言转命令**: 使用 LLM 将自然语言描述转换为命令行指令
- **双工具支持**: 支持 FFmpeg（视频处理）和 Pandoc（文档转换）
- **安全检查**: 内置危险命令检测，防止执行恶意操作
- **JSON 配置**: 使用 JSON 文件配置 LLM 连接信息
- **交互式确认**: 执行前显示生成命令，用户确认后执行

## 环境依赖

- **C++ 编译器**: clang++ 21+ (支持 C++17 标准)
- **CMake**: 4.0.0 及以上版本
- **第三方库**:
  - libcurl (CURL 请求)
  - nlohmann-json (JSON 解析)
- **系统工具**: FFmpeg, Pandoc
- **网络**: 需要 Internet 连接以访问 LLM API

## 项目结构

```
NLTools/
├── main.cpp                 # 主程序入口
├── CMakeLists.txt           # CMake 构建配置
├── config.json              # LLM 配置文件
├── include/                 # 头文件目录
│   ├── config.h            # 配置加载类
│   ├── llm_service.h      # LLM 服务类
│   └── exec.h              # 命令执行类
├── src/                     # 源文件目录
│   ├── config.cpp          # 配置加载实现
│   ├── llm_service.cpp     # LLM 服务实现
│   └── exec.cpp            # 命令执行实现
└── build/                   # 构建目录
```

## 编译步骤

```bash
# 1. 创建构建目录
mkdir build && cd build

# 2. 配置项目
cmake ..

# 3. 编译
make -j$(nproc)

# 4. 运行
./NLTools
```

## 配置说明

编辑 `config.json` 文件，配置 LLM 连接信息：

```json
{
    "model_endpoint": "https://api.longcat.chat/openai/v1/chat/completions",
    "api_key": "your_api_key_here",
    "model_name": "LongCat-Flash-Lite"
}
```

| 配置项              | 说明             |
| ---------------- | -------------- |
| `model_endpoint` | LLM API 端点 URL |
| `api_key`        | API 密钥         |
| `model_name`     | 使用的模型名称        |

## 使用方法

```
1. 选择模式: 0 = FFmpeg, 1 = Pandoc
2. 输入自然语言描述需求
3. 输入输入文件路径
4. 输入输出文件路径
5. 查看生成的命令
6. 确认是否执行 (Y/n)
```

### 使用示例

```
plz input mode: (0 for ffmpeg, 1 for pandoc) 0
plz input Natural Language about how you wanna to do with this file
我想要将input.mp4转换为gif格式
where's the input file?
input.mp4
what about the outputFile?
output.gif
output: ffmpeg -i input.mp4 -vf "fps=10,scale=320:-1" output.gif
Execute? (Y/n) Y
```

## 模块说明

| 模块           | 功能                           |
| ------------ | ---------------------------- |
| `llmConfig`  | 从 JSON 文件加载 LLM 配置           |
| `LLMService` | 生成 Prompt 并通过 CURL 与 LLM 通信  |
| `cmdExec`    | 解析 LLM 返回的 JSON，检测命令安全性，执行命令 |
| `main`       | 主程序，协调各模块工作                  |

## License

MIT License - see [LICENSE](LICENSE) file for details.
