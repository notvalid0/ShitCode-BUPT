# 参考学习https://zhuanlan.zhihu.com/p/608317982 && 官方文档
cmake_minimum_required(VERSION 4.0.0)#因为我的版本是4.3.1
project(NLTools)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(${PROJECT_NAME} main.cpp
    src/config.cpp
    src/exec.cpp
    src/llm_service.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl nlohmann_json::nlohmann_json)
