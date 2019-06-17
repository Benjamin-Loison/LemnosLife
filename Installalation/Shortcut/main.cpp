#include <string>
#include <fstream>
#include "shlobj.h"
using namespace std;

int main() /// TODO: remove useless console(installer works well without it) come from project settings I think (initial) if needed try to recreate a EMPTY PROJECT
{
    /*int hConHandle;
    long lStdHandle;
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    FILE *fp;
    AllocConsole();
    SetConsoleTitle("");
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);
    lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen(hConHandle, "w");
    *stdout = *fp;
    setvbuf(stdout, NULL, _IONBF, 0);
    lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen(hConHandle, "r");
    *stdin = *fp;
    setvbuf(stdin, NULL, _IONBF, 0);
    lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen(hConHandle, "w");
    *stderr = *fp;
    setvbuf(stderr, NULL, _IONBF, 0);
    ios::sync_with_stdio();*/
    string name = "LemnosLife .exe";
    ifstream installer(name.c_str());
    if(installer.good())
    {
        installer.close();
        while(remove(name.c_str()) == -1);
    }
    char pathSeparator =
    #ifdef _WIN32
        '\\';
    #else
        '/';
    #endif
    TCHAR szPath[MAX_PATH];
    SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, szPath);
    string tmp = string(szPath) + pathSeparator + "LemnosLife" + pathSeparator + "Games" + pathSeparator + "LemnosLife" + pathSeparator + "Updater" + pathSeparator, path = tmp + "LemnosLife-MAJ.exe";
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
