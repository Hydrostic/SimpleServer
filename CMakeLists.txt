cmake_minimum_required(VERSION 3.22.1)

set(PROJECT_NAME SimpleServer)
project(${PROJECT_NAME} VERSION 0.0.1)

# file(GLOB_RECURSE SOURCES src/*.cpp)
set(SRC_FILES src/http_tcp_server.cpp src/io/buffer.cpp src/utils/io_wrapper.cpp src/protocol/http/kinds.cpp src/protocol/http/request.cpp src/protocol/http/response.cpp src/protocol/http/parse.cpp)
add_executable(${PROJECT_NAME} src/main.cpp)
include_directories(src)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_FILES})

set(CMAKE_CXX_STANDARD, 17)
include(FetchContent)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog
    GIT_TAG        27cb4c7
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt
    GIT_TAG        0c9fce2
)
FetchContent_MakeAvailable(fmt)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt spdlog)
# target_link_libraries(${PROJECT_NAME} PUBLIC src)