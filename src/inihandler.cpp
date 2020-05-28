/*
Ini handler routines
*/
#include <inihandler.hpp>
#include <inih/cpp/INIReader.h>
#include <iostream>
#include <string>

using namespace std;

int readIni(const string &iniF) {
    INIReader reader(iniF);

    if (reader.ParseError() < 0) {
        std::cout << "Can't load " << iniF <<"\n";
        return 1;
    }
    std::cout << "Config loaded from 'test.ini': version="
              << reader.GetInteger("protocol", "version", -1) << ", name="
              << reader.Get("user", "name", "UNKNOWN") << ", email="
              << reader.Get("user", "email", "UNKNOWN") << ", pi="
              << reader.GetReal("user", "pi", -1) << ", active="
              << reader.GetBoolean("user", "active", true) << "\n";
    std::cout << "Has values: user.name=" << reader.HasValue("user", "name")
              << ", user.nose=" << reader.HasValue("user", "nose") << "\n";
    std::cout << "Has sections: user=" << reader.HasSection("user")
              << ", fizz=" << reader.HasSection("fizz") << "\n";
    return 0;
}