cmake_minimum_required(VERSION 3.10)
project(EzCryptoCpp)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 包含头文件路径
include_directories(include)

# 查找所有源文件
file(GLOB SOURCES "src/*.cpp" "tests/*.cpp")

# 添加可执行文件
add_executable(EzCryptoCpp ${SOURCES} "tests/main.cpp" )
