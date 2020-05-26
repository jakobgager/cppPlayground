# CMakeLists.txt

cmake_minimum_required(VERSION 3.4)

project(cppPlayground VERSION 1.0
                      DESCRIPTION "Very nice project")

include_directories( ./lib )

add_executable(cppPlayground src/main.cpp lib/inih/ini.c lib/inih/cpp/INIReader.cpp)
