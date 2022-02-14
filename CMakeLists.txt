cmake_minimum_required(VERSION 3.21)
project(DependManager)

find_package(PkgConfig)
pkg_check_modules(PackageKit REQUIRED IMPORTED_TARGET packagekit-glib2)
include_directories(${PackageKit_INCLUDE_DIRS})

# 调试时需要此文件
file(COPY info.lua DESTINATION ${PROJECT_BINARY_DIR}/src/xmake)

add_subdirectory(src)