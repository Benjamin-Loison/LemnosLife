#include <string>
#include "shlobj.h"
#include <iostream>
#include <fcntl.h>
using namespace std;

string name = "TerraCraft", resources[] = {"LemnosLife - MAJ.exe", "libcurl-x64.dll", "libfreetype-6.dll", "libjpeg-9.dll", "SDL2.dll", "SDL2_image.dll", "SDL2_ttf.dll", "libgcc_s_seh-1.dll", "zlib1.dll", "libcrypto-1_1-x64.dll", "libssl-1_1-x64.dll", "arial.ttf", "background.jpg", "libwinpthread-1.dll", "msvcr120.dll", "LemnosLife.exe", "unzip.exe", "unzip32.dll", "libstdc++-6.dll"};

// TODO: faster

bool extractResource(DWORD resId, LPCTSTR fileName)
{
    HRSRC hRes = FindResource(0, (LPTSTR)resId, RT_RCDATA);
    LPVOID lpRes = LockResource(LoadResource(0, hRes));
    DWORD dwSize = SizeofResource(0, hRes), dwWrite = -1;
    if(lpRes && dwSize)
    {
        HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
        if(hFile != INVALID_HANDLE_VALUE)
        {
            WriteFile(hFile, lpRes, dwSize, &dwWrite, 0);
            CloseHandle(hFile);
        }
    }
    return dwWrite == dwSize;
}

/// need to unlink/link when update LemnosLife - MAJ for instance

int main()
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
    char pathSeparator =
    #ifdef _WIN32
        '\\';
    #else
        '/';
    #endif
    //TCHAR szPath[MAX_PATH];
    //SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, szPath);
    string tc = string(getenv("APPDATA")) + pathSeparator + name + pathSeparator, game = tc + "Games" + pathSeparator, ac = game + "LemnosLife" + pathSeparator, path = ac + "Updater" + pathSeparator;
    cout << tc;    CreateDirectory(tc.c_str(), NULL);
    CreateDirectory(game.c_str(), NULL);
    CreateDirectory(ac.c_str(), NULL);
    CreateDirectory(path.c_str(), NULL);
    for(unsigned short i = 0; i < 19; i++) // should make a cleaner way not to "rewrite" this number
        if(resources[i] != "LemnosLife.exe")
            extractResource(i, string(path + resources[i]).c_str());
        else
            extractResource(i, resources[i].c_str());
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    CreateProcess("LemnosLife.exe", NULL, NULL, NULL, FALSE, /*0*/CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}
