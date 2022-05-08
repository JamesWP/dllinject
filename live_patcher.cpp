#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <iostream>
#include <fstream>

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved )  // reserved
{
    std::ofstream logfile;

    logfile.open("test_library.log", std::ios_base::app); // append instead of overwrite

    // Perform actions based on the reason for calling.
    switch( fdwReason ) 
    { 
        case DLL_PROCESS_ATTACH:
            logfile << std::endl << "-----------------------" << std::endl;
            logfile << "Initializing test_library" << std::endl;
            // Initialize once for each new process.
            // Return FALSE to fail DLL load.
            break;

        case DLL_THREAD_ATTACH:
            logfile << "Initializing test_library: THREAD_ATTACH" << std::endl;
            // Do thread-specific initialization.
            break;

        case DLL_THREAD_DETACH:
            logfile << "Deinitializing test_library: THREAD_ATTACH" << std::endl;
            // Do thread-specific cleanup.
            break;

        case DLL_PROCESS_DETACH:
            // Perform any necessary cleanup.
            logfile << "Deinitializing test_library" << std::endl;
            break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}

extern "C" {
__declspec(dllexport) int blah() {
    std::cout << "imported" << std::endl;
    return 0;
}
}