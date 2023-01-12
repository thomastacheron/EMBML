cmake_minimum_required(VERSION 3.0.2)
project(wav_parser LANGUAGES CXX)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++2a")

file(
GLOB_RECURSE
source_files
src/main.cpp
)

add_executable(
${PROJECT_NAME}
${source_files}
)

target_link_libraries(${PROJECT_NAME} PUBLIC)
