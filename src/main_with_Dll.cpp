#ifndef USE_PRECOMPILED_HEADERS
    #ifdef WIN32
        #include <direct.h>
        #include <windows.h>
    #else
        #include <sys/types.h>
        #include <dlfcn.h>
    #endif

    #include <tclap/CmdLine.h>
    #include <iostream>
    #include <vector>
    #include <string>
#endif

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

    // load dynamic library
    #ifdef WIN32
        HINSTANCE lib_handle;
    #else
        void *lib_handle;
    #endif

    // Where retType is the pointer to a return type of the function
    // This return type can be int, float, double, etc or a struct or class.

    typedef int (*func_t)(string);  

    // load the library -------------------------------------------------
    #ifdef WIN32
        string nameOfLibToLoad("libinih.dll");
        lib_handle = LoadLibrary(TEXT(nameOfLibToLoad.c_str()));
        if (!lib_handle) {
            cerr << "Cannot load library: " << TEXT(nameOfLibToLoad.c_str()) << endl;
        }
    #else
        string nameOfLibToLoad("libinih.so");
        lib_handle = dlopen(nameOfLibToLoad.c_str(), RTLD_LAZY);
        if (!lib_handle) {
            cerr << "Cannot load library: " << dlerror() << endl;
        }
    #endif

    // load the symbols -------------------------------------------------
    #ifdef WIN32
        // silence casting error (see e.g. https://github.com/sumogr/monero/commit/13e1668bb4334af2bc314444b7ea738db084ce62)
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wcast-function-type"
        func_t readIni = (func_t) GetProcAddress(lib_handle, "readIni");
        #pragma GCC diagnostic pop
        if (!readIni) {
            cerr << "Cannot load symbol readIni: " << GetLastError() << endl;
        }
    #else
        // reset errors
        dlerror();

        // load the symbols (handle to function "")
        func_t readIni= (func_t) dlsym(lib_handle, "readIni");
        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            cerr << "Cannot load symbol readIni: " << dlsym_error << endl;
        }
    #endif

    readIni(iniF);

    // unload the library -----------------------------------------------

    #ifdef WIN32
        FreeLibrary(lib_handle);
    #else
        dlclose(lib_handle);
    #endif
}
