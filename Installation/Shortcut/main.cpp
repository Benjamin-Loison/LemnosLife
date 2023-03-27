#include <string>
#include "shlobj.h"
using namespace std;

/// TODO: make a graphical message if the destination executable path isn't reachable
int main()
{
    /*string name = "LemnosLife - Installeur.exe";
    ifstream installer(name.c_str());
    if(installer.good())
    {
        installer.close();
        while(remove(name.c_str()) == -1);
    }*/
    char pathSeparator =
    #ifdef _WIN32
        '\\';
    #else
        '/';
    #endif
    string tmp = string(getenv("APPDATA")) + pathSeparator + "TerraCraft" + pathSeparator + "Games" + pathSeparator + "LemnosLife" + pathSeparator + "Updater" + pathSeparator,
           path = tmp + "LemnosLife - MAJ.exe";
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    CreateProcess(path.c_str(), NULL, NULL, NULL, FALSE, 0, NULL, tmp.c_str(), &si, &pi);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}
