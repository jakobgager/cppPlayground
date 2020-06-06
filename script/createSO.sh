#! /bin/sh
g++ -Wall -fPIC -I../src -I../lib -c ../src/inihandler.cpp ../lib/inih/ini.c ../lib/inih/cpp/INIReader.cpp
g++ -shared -Wl,-soname,libinih.so.1 -o libinih.so.1.0 inihandler.o ini.o INIReader.o
ln -sf libinih.so.1.0 libinih.so.1
ln -sf libinih.so.1.0 libinih.so

