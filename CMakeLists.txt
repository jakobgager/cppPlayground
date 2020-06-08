# CMakeLists.txt

cmake_minimum_required(VERSION 3.4)

project(cppPlayground VERSION 1.0
                      DESCRIPTION "Very nice project")

include_directories( ./lib ./src)
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# basic compile
add_executable(cppPlayground 
    src/main.cpp src/inihandler.cpp 
    lib/inih/ini.c lib/inih/cpp/INIReader.cpp)

# Create shared Library (dll, so)
add_library(inihandler SHARED src/inihandler.cpp lib/inih/ini.c lib/inih/cpp/INIReader.cpp)
#set_target_properties(inihandler PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../dll)
set_target_properties(inihandler PROPERTIES OUTPUT_NAME inih)
set_target_properties(inihandler PROPERTIES VERSION "1.0")
#add_custom_command(TARGET inihandler PRE_BUILD COMMAND mkdir ../dll)
if (UNIX)
    add_custom_command(TARGET inihandler POST_BUILD
                   COMMAND ln -sf libinih.so.1.0 libinih.so.1
                   COMMAND ln -sf libinih.so.1.0 libinih.so)
    #              WORKING_DIRECTORY ../dll)
endif()

# compile with linked shared lib
add_executable(cppPlaygroundDll src/main.cpp)
#target_link_directories(cppPlaygroundDll PRIVATE ../dll)
target_link_libraries(cppPlaygroundDll inihandler)

# compile with runtime shared lib
add_executable(cppPlaygroundDll_Dyn src/main_with_Dll.cpp)
if (UNIX)
    target_link_libraries(cppPlaygroundDll_Dyn dl)
    target_compile_options(cppPlaygroundDll_Dyn PRIVATE -rdynamic)
endif()
