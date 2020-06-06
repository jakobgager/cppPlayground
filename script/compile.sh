#! /bin/sh
##g++ -Wall -L../dll -I../src -I../lib ../src/main.cpp -lini ../lib/inih/ini.c ../lib/inih/cpp/INIReader.cpp -o playSO
g++ -Wall -L../dll -I../src -I../lib ../src/main.cpp -linih -o playSO
