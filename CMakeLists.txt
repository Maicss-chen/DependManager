cmake_minimum_required(VERSION 3.21)
project(DependManager)

# 调试时需要此文件
file(COPY info.lua DESTINATION ${PROJECT_BINARY_DIR}/src/xmake)

add_subdirectory(src)