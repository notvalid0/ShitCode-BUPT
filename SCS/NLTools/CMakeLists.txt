cmake_minimum_required(VERSION 4.0.0)
project(NLTools)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

# FTXUI via FetchContent
include(FetchContent)
FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
    GIT_TAG        v5.0.0
)
FetchContent_MakeAvailable(ftxui)

add_executable(${PROJECT_NAME}
    main.cpp
    src/config.cpp
    src/exec.cpp
    src/llm_service.cpp
    ui/ui.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE
    CURL::libcurl
    nlohmann_json::nlohmann_json
    ftxui::component
    ftxui::dom
    ftxui::screen
)
