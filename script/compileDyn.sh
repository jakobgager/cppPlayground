#! /bin/sh
##g++ -Wall -rdynamic -I../src -I../lib ../src/main_with_Dll.cpp ../lib/inih/ini.c ../lib/inih/cpp/INIReader.cpp -ldl -o playSO_dyn
g++ -Wall -rdynamic -I../src -I../lib ../src/main_with_Dll.cpp -ldl -o playSO_dyn
