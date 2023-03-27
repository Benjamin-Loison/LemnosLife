#include <string>
#include "shlobj.h"

#include <sys/stat.h>

#define RESOURCES_NB 12
using namespace std;

string name = "TerraCraft", resources[] = {"LemnosLife - MAJ.exe", "libcurl-x64.dll", "libfreetype-6.dll", "SDL2.dll", "SDL2_image.dll", "SDL2_ttf.dll",
                                           "libgcc_s_seh-1.dll", "zlib1.dll", "arial.ttf", "background.jpg", "libwinpthread-1.dll", "libstdc++-6.dll"};

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

/// need to unlink/link when update LemnosLife - MAJ for instance - ?

bool doesFileExist(string name)
{
    struct stat buffer;
    return stat(name.c_str(), &buffer) == 0;
}

char pathSeparator =
#ifdef _WIN32
    '\\';
#else
    '/';
#endif

int main()
{
    string tc = string(getenv("APPDATA")) + pathSeparator + name + pathSeparator,
           game = tc + "Games" + pathSeparator,
           ll = game + "LemnosLife" + pathSeparator,
           path = ll + "Updater" + pathSeparator,
           maj = path + "LemnosLife - MAJ.exe";
    //cout << tc;
    if(!doesFileExist(path + resources[RESOURCES_NB - 1]))
    {
        CreateDirectory(tc.c_str(), NULL);
        CreateDirectory(game.c_str(), NULL);
        CreateDirectory(ll.c_str(), NULL);
        CreateDirectory(path.c_str(), NULL);

        for(unsigned short i = 0; i < RESOURCES_NB; i++)
        {
            //if(resources[i] != "LemnosLife.exe")
                extractResource(i, string(path + resources[i]).c_str());
            //else
            //    extractResource(i, resources[i].c_str());
        }
    }
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    //CreateProcess(/*"LemnosLife.exe"*/maj.c_str(), NULL, NULL, NULL, FALSE, /*0*/CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
    CreateProcess(maj.c_str(), NULL, NULL, NULL, FALSE, /*0 not defined by spec*/CREATE_NO_WINDOW, NULL, path.c_str(), &si, &pi);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

