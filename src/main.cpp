#include <tclap/CmdLine.h>
#include <inih/cpp/INIReader.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

//declaration of readIni
int readIni(const string &iniF);

// **************************************
int main(int argc, char* argv[])
{
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};
    string name;
    string iniF;
    try {  
	    TCLAP::CmdLine cmd("Command description message", ' ', "0.9");
	    TCLAP::ValueArg<std::string> nameArg("n","name","Name to print",false,"homer","string");
	    TCLAP::ValueArg<std::string> iniArg("","ini","Ini-File",false,"","string");
	    cmd.add( nameArg );
	    cmd.add( iniArg );
	    // Parse the argv array.
	    cmd.parse( argc, argv );
        // Get the value parsed by each arg. 
        name = nameArg.getValue();
        iniF = iniArg.getValue();
        // cout << "My name is: " << name << std::endl;
	} catch (TCLAP::ArgException &e)  // catch any exceptions
	{ std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; }
    
    int i = 0;
    
    for (const string &word : msg)
    {
        cout << word << " ";
        ++i;
    }
    cout << endl;
    cout << "My name is: " << name << std::endl;
    readIni(iniF);
}

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