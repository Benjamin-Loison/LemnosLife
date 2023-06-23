#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <sstream>
#include <sys/time.h>
///#define _WIN32_WINNT 0x0501 //this is for XP
#include <windows.h>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define stat _stat
#include <vector>
using namespace std;

// most code copied from client side
string exec(const char* cmd), getDate(), uploadFile(string url, string fieldName, string filePath), getFileContentString(string path), getLastModifiedFile(string folder);
bool contains(string subject, string find), writeFile(string filePath, string option, string toWrite);
void log(string toLog);

string gdbCmd = "",//"-ex \"set pagination off\" -ex \"set confirm off\" -ex \"set print thread-events off\" -ex \"handle SIGTRAP nostop noprint noignore\" -ex \"file LemnosLife.exe\" ", // can maybe not use "file" commands to specify the executable cf start.sh on server side
       crashNeedle = " received signal SIGSEGV, Segmentation fault.",//"Program received signal SIGSEGV, Segmentation fault.",
       extensionsFolder = "Extensions\\",
       crashFolder = extensionsFolder + "Crashes\\",
       logCrashReportFile = "crash-report.txt";

int main()
{
    ///ShowWindow (GetConsoleWindow(), SW_HIDE);

    //while(true) Sleep(1);
    log("Starting...");
    string crashFile = crashFolder + getDate() + ".crash";
    log("CrashFile: " + crashFile); /// could log but only when crash (use a temporary vector<string> while waiting a potential crash)
    gdbCmd += "-ex \"set logging file " + crashFile + "\" -ex \"set logging on\""/*" -ex \"r\" -ex \"bt f\" -ex q"*/;
    log("gdbCmd: " + gdbCmd);
    //gdbCmd += " > " + crashFile;
    //WinExec(gdbCmd.c_str(), SW_HIDE);

    SHELLEXECUTEINFO ShExecInfo = {0};
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    ShExecInfo.lpFile = "gdb\\gdbAttach.bat";//"gdb.exe"; // yse gdbAttach otherwise vocal chat doesn't work (encoding to .wav doesn't work for instance)
    ShExecInfo.lpParameters = gdbCmd.c_str();
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = SW_HIDE;
    ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo);
    log("Started...");
    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
    log("No more waiting");
    CloseHandle(ShExecInfo.hProcess);
    log("Handle closed");

    //system(gdbCmd.c_str());
    //string res = exec(gdbCmd.c_str());
    string res = getFileContentString(crashFile);
    log("crash content: " + res); // used to be print
    if(contains(res, crashNeedle))
    {
        //writeFile(crashFile, "w", res);
        //log("Crash found, uploading...");
        log("Crash found, now looking for latest log...");
        // could also change crash then log to log then crash
        string lastLog = getLastModifiedFile(extensionsFolder + "Logs\\");
        log("lastLog: " + lastLog + "!");
        string fileContent = getFileContentString(lastLog);
        writeFile(crashFile, "a", "\nLogs:\n" + fileContent); // may also think about sending crash logs in case didn't work fine in the past - but let say no
        log("Latest log found, now uploading...");
        uploadFile("https://lemnoslife.com/crash-report.php", "crash-report", crashFile);
        log("Crash uploaded !");
    }
    else
    {
        log("Crash needle not found !");
    }
    return 0;
}

unsigned long long getLastModifiedTime(string file) // could also just look at filenames - let's do this because in theory faster - well let say no because when there is a one hour time shift it may involve problems
{
    struct stat result;
    if(stat(file.c_str(), &result)==0)
    {
        unsigned long long mod_time = result.st_mtime;
        return mod_time;
    }
    return 0;
}

vector<string> listFiles(string directory, string extension)
{
    WIN32_FIND_DATA findData;
    string fileLookingFor = directory + "*" + extension;
    HANDLE hFind = FindFirstFile(fileLookingFor.c_str(), &findData);
    vector<string> files;
    if(hFind == INVALID_HANDLE_VALUE)
        return files;
    do
    {
        string fileName = findData.cFileName;
        files.push_back(fileName);
    } while(FindNextFile(hFind, &findData) > 0);
    return files;
}

template<typename T>
string convertNbToStr(const T& number)
{
    ostringstream convert;
    convert << number;
    return convert.str();
}

string getLastModifiedFile(string folder)
{
    string res = "";
    unsigned long long lastModifiedTime = 0;
    vector<string> files = listFiles(folder, ".log");
    unsigned int filesSize = files.size();
    for(unsigned int filesIndex = 0; filesIndex < filesSize; filesIndex++)
    {
        string file = folder + files[filesIndex]; // could also just return the fileName and add before the folder already known
        unsigned long long fileTime = getLastModifiedTime(file);
        //log(file + " " + convertNbToStr(fileTime) + "!");
        if(fileTime > lastModifiedTime)
        {
            res = file;
            lastModifiedTime = fileTime;
        }
    }
    return res;
}

void log(string toLog)
{
    toLog = getDate() + ": " + toLog + "\n";
    writeFile(logCrashReportFile, "a", toLog);
}

string getFileContentString(string path)
{
    ifstream infile(path.c_str());
    string line, res = "";
    while(getline(infile, line))
        res += line + "\n";
    return res;
}

bool writeFile(string filePath, string option, string toWrite)
{
    FILE* file = fopen(filePath.c_str(), option.c_str());
    if(file != NULL)
    {
        fputs(toWrite.c_str(), file);
        fclose(file);
        return true;
    }
    return false;
}

string getNbZero(double number)
{
    string strNb = convertNbToStr(number);
    for(unsigned short digit = strNb.length(); digit < 2; digit++)
        strNb = "0" + strNb;
    return strNb;
}

unsigned long long getMillis()
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return (long long)tp.tv_sec * 1000L + tp.tv_usec / 1000;
}

string getDate()
{
    time_t t = time(0);
    struct tm *now = localtime(&t);

    return getNbZero(now->tm_mday) + "-" + getNbZero(now->tm_mon + 1) + "-" + convertNbToStr<int>(now->tm_year - 100) + "#" + getNbZero(now->tm_hour) + "-" + getNbZero(now->tm_min) + "-" + getNbZero(now->tm_sec);
}

bool contains(string subject, string find)
{
    return subject.find(find) != string::npos;
}

/*string exec(const char* cmd) // we want to have stderr too !
{
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if(!pipe)
        throw runtime_error("popen() failed!");
    while(fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
        result += buffer.data();
    return result;
}*/

/*void print(string s)
{
    cout << s << endl;
}*/

struct MemoryStruct
{
    char *memory;
    size_t size;
};

static size_t writeMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct* mem = (struct MemoryStruct *)userp;

    mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
    if(mem->memory == NULL)
    {
        log("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

string uploadFile(string url, string fieldName, string filePath)
{
    string toReturn = "";
    struct curl_httppost* formpost = NULL, *lastptr = NULL;

    curl_global_init(CURL_GLOBAL_ALL);

    curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, fieldName.c_str(), CURLFORM_FILE, filePath.c_str(), CURLFORM_END);
    curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "submit", CURLFORM_COPYCONTENTS, "send", CURLFORM_END);

    CURL* curl = curl_easy_init();

    if(curl)
    {
        struct MemoryStruct chunk;

        chunk.memory = (char*)malloc(1);
        chunk.size = 0;

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "LemnosLifeCrashReporter");

        struct curl_slist* headerlist = NULL;
        static const char buf[] = "Expect:";
        headerlist = curl_slist_append(headerlist, buf);

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        #ifdef _WIN32
            curl_easy_setopt(curl, CURLOPT_SSL_OPTIONS, CURLSSLOPT_NATIVE_CA);
        #endif

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        //curl_easy_setopt(curl, CURLOPT_TIMEOUT, 0); // used to be 1 - 0 is infinite (default) (was about to put 10)

        CURLcode res = curl_easy_perform(curl);

        if(res == CURLE_OK)
            toReturn = chunk.memory;
        else if(CURLE_OPERATION_TIMEDOUT == res)
        {
            log("time out curl");
        }
        else
        {
            log("curl_easy_perform() failed: " + string(curl_easy_strerror(res)));
        }

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(headerlist);
    }
    return toReturn;
}
