#include <inihandler.hpp>
#include <tclap/CmdLine.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// **************************************
int main(int argc, char* argv[])
{
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};
    string name;
    string iniF;
    try {  
	    TCLAP::CmdLine cmd("Command description message", ' ', "0.9");
	    TCLAP::ValueArg<std::string> nameArg("n","name","Name to print",false,"homer","string");
	    TCLAP::ValueArg<std::string> iniArg("","ini","Ini-File",false,"data/test.ini","string");
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
