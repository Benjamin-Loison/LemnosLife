#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <thread>
#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <fstream>
#include <curl/curl.h>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include "patch.h"
#include <deque>
#include <map>
#include <windows.h>
//#include <zipper/unzipper.h>
//#include <zipper/zipper.h>
#define lengthActualVersion 50
using namespace std;

char actualVersion[lengthActualVersion], pathSeparator;
SDL_Window* screen;
TTF_Font* font24, *font35;
string getInternet(string), updateLine = "Chargement en cours...", fileDownload = "", versionDownload = "", unit = "", gameFolder = "", majFile = "MAJ.info", path = "", folder = "", httpsPrefix = "https:", maj = "", currentVersion = "", logPath = "log.txt";
vector<string> filesToDownload;
map<string, vector<string>> changeFilesVersion;
deque<string> changeLogTmp, changeLog;
thread updateThread, updaterThread;
double progress = 0, amountDownloaded = 0, amountToDownload = 0, unitDiv = 0;
void eventManager(), renderScreen(), updateManager(), free(), size(), launch(bool), downloadFileInternet(string, string), updateScreen();
int windowWidth = 0, windowHeight = 0, posY = 0, rendered = 0;
GLuint background = 0, loadTexture(const char*);
unsigned long getFileSize(/*string*/vector<string>);
bool rendering = false, title = true, firstLaunch = false, needUpdate(), textInit = false, downloadInit = false, isEnd = false, removeFile(string filePath);
unsigned short latestVersionNumber, currentVersionNumber;

// TODO: update this updater and add future updates
// TODO: make possibility to choose language for changelogs
// updater of the updater ?
/// TODO: upload all components (Updater, Shortcut...) as 64 bits for the 64 bits version likewise 32-bits users would be told directly
/// TODO: is the updater at the bottom working for various versions ?
/// TODO: scrool doesn't work well

// warnin 32/64 bits and where the exe is generated for installer, updater and shortcut codeblocks projects
int main(int argc, char** argv) // downloading zip and unzip may be (at least use less bandwidth, 75 instead of 115 for example) what about speed ?
{
    //cout << "main" << endl;
    pathSeparator =
    #ifdef _WIN32
        '\\';
    #else
        '/';
    #endif
    gameFolder = string("..") + pathSeparator + "Game" + pathSeparator;
    char psBuffer[128];
    FILE *pPipe;
    if((pPipe = _popen("cd", "rt")) == NULL) // what does this do ?
        exit(1);
    fgets(psBuffer, 128, pPipe);
    for(unsigned short i = 0; i < 128; i++)
        if(psBuffer[i] == '\n')
            psBuffer[i] = '\0';
    _pclose(pPipe);
    path = psBuffer;
    //removeFile(logPath);
    /// TODO: add date in print
    if(!needUpdate())
    {
        //cout << "no update needed !";
        launch(true);
    }
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayMode DM;
    SDL_GetDesktopDisplayMode(0, &DM);
    windowWidth = 1365;
    windowHeight = 704;
    screen = SDL_CreateWindow(name.c_str(), 100, 100, windowWidth, windowHeight, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL); // could do without opengl lol
    size();
    TTF_Init();
    updateManager();
    free();
    return 0;
}

bool isAlphabetic(char chr)
{
    return (chr >= 65 && chr <= 90) || (chr >= 90 && chr <= 123);
}

template<typename Out>
void split(const string &s, const char *delim, Out result)
{
    stringstream ss;
    ss.str(s);
    string item;
    while(getline(ss, item, *delim))
        *(result++) = item;
}

vector<string> split(const string &s, const char *delim = " ")
{
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}

string replace(string subject, const string& search, const string& replace)
{
    unsigned int pos = subject.find(search);
    return pos > subject.length() ? subject : subject.replace(pos, search.length(), replace);
}

string convertNbToStr(double number)
{
    ostringstream convert;
    convert << number;
    return convert.str();
}

long convertStrToLong(string str) // really necessary file size ? yes because otherwise only around 1 Gb
{
    return atol(str.c_str());
}

int convertStrToInt(string str)
{
    int number;
    sscanf(str.c_str(), "%d", &number);
    return number;
}

void chgGameFolder()
{
    folder = replace(gameFolder, "..", "");
    folder = folder.substr(0, folder.length()); // does it really change something ?
    path = path.substr(0, path.find_last_of(pathSeparator)) + folder;
}

void startup(LPCTSTR lpApplicationName)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    CreateProcess(lpApplicationName, NULL, NULL, NULL, FALSE, 0, NULL, string(path + pathSeparator).c_str(), &si, &pi);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

void launch(bool start)
{
    //if(start)
        chgGameFolder();
    string game = string(path + "CrashReporter.exe");
    //cout << "!" << game << "!" << path << "CrashReporter.exe" << "!" << endl;
    startup(game.c_str());
    if(!start)
    {
        isEnd = true;
        updateScreen();
    }
    else
        exit(0);
}

string getFileContentString(string path)
{
    ifstream infile(path.c_str());
    string line, res = "";
    while(getline(infile, line))
        res += line;
    return res;
}

string replaceAll(string str, const string& from, const string& to = "")
{
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

unsigned short cleanVersion(unsigned short x)
{
    if(x < 1000)
        x *= 10;
    if(x < 1000)
        x *= 10;
    return x;
}

bool needUpdate()
{
    // TODO: crypt content without homemade (compare local and server crypted version) /// THINK AGAIN AT THE SYSTEM (user knows version not crypted and can crypt himself or ask friends)
    maj = getInternet("http://lemnoslife.com/MAJLatest.txt");
    currentVersion = getFileContentString(majFile); // does it work fine even if file doesn't exist ?
    currentVersionNumber = cleanVersion(currentVersion == "" ? 0 : convertStrToInt(currentVersion));
    latestVersionNumber = cleanVersion(convertStrToInt(replaceAll(maj, ".")));
    //cout << latestVersionNumber << " " << currentVersionNumber << " (" << currentVersion << ")" << endl;
    return latestVersionNumber > currentVersionNumber;
}

bool startsWith(string subject, string test)
{
    return !subject.compare(0, test.size(), test);
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

bool removeFile(string filePath)
{
    return remove(filePath.c_str());
}
// is there on a frame a console before launching updater etc ? see Installer and Shortcut programs

void print(string s)
{
    //cout << s << endl;
    writeFile(logPath, "a", s + "\n");
}

void updater()
{
    //cout << "hey" << endl;
    updateLine = "Chargement des méta-données de la mise à jour...";
    if(currentVersion == "")
    {
        currentVersion = maj;
        print("Installing from scratch");
    }
    string majFolder = "http://lemnoslife.com/MAJ/" + currentVersion + "/", url = majFolder + "changelogs.txt", changelogs = getInternet(url);
    vector<string> lines = split(changelogs, "\n");
    //cout << "!" << changelogs << "!" << url << "!" << majFolder << "!" << endl;
    print("Downloading: " + url);
    if(lines[0] == "WithZIP")
    {
        print("WithZIP");
        if(currentVersionNumber == 0)
            CreateDirectory(gameFolder.c_str(), NULL);
        //downloadFileHttp(majFolder + "changes.zip");
        /// TODO: progress = 0; 50 % download and 50 % deflating
        updateLine = "Téléchargement de la mise à jour...";
        string urlZIP = "lemnoslife.com/MAJ/" + currentVersion + "/changes.zip";
        print("Downloading: " + urlZIP);
        downloadFileInternet(urlZIP, "../Game/changes.zip");
        updateLine = "Décompression de l'archive...";
        ///system("cd ../Game/ && unzip.exe -o -q changes.zip && del changes.zip"); // this suddenly display a console
        //chgGameFolder();
        print("Extracting...");
        SHELLEXECUTEINFO ShExecInfo = {0};
        ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
        ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
        ShExecInfo.hwnd = NULL;
        ShExecInfo.lpVerb = NULL;
        ShExecInfo.lpFile = "unzip.exe"; // no '/' :'( // ..\\Updater\\ doesn't seem to work O_o
        ShExecInfo.lpParameters = "-o -q ..\\Game\\changes.zip -d ..\\Game\\";
        ShExecInfo.lpDirectory = NULL;
        ShExecInfo.nShow = SW_HIDE;
        ShExecInfo.hInstApp = NULL;
        ShellExecuteEx(&ShExecInfo);
        WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
        CloseHandle(ShExecInfo.hProcess);
        print("Extracted !");
        removeFile("..\\Game\\changes.zip");

        // add parameter to force unzip (if someone stop updater while proceding) - done
        // using libraries would be cleaner
        /*Unzipper unzipper("changes.zip");
        unzipper.extract();
        unzipper.close();*/
    }
    updateLine = "Suppression d'anciens fichiers...";
    unsigned int linesSize = lines.size();
    for(unsigned int linesIndex = 1; linesIndex < linesSize; linesIndex++)
    {
        string line = gameFolder + lines[linesIndex];
        if(line[line.length() - 1] == '/')
        {
            RemoveDirectory(line.c_str());
            //removeFolder(line);
        }
        else
        {
            removeFile(line);
        }
    }
    print("Update done !");
    updateLine = "Mise à jour terminée !";
    writeFile(majFile, "w", maj);
    // TODO: if friends send files, find files like steam
    // TODO: delete system - instead of +
    launch(false);
}

bool first = true;

void updateScreen()
{
    if(first)
    {
        vector<string> news = split(getInternet("http://lemnoslife.com/MAJ.txt"), "\n");
        for(unsigned int i = 0; i < news.size(); i++)
        {
            changeLog.push_back(news[i]);
        }
        changeLogTmp = changeLog;
        first = false;
    }
    SDL_Event patch; // why this ?
    patch.type = SDL_MOUSEBUTTONDOWN;
    SDL_PushEvent(&patch);
}

void update()
{
    while(true)
    {
        updateScreen();
        SDL_Delay(/*15*/100); // used to be 30
    }
}

void updateManager()
{
    font24 = TTF_OpenFont("arial.ttf", 24);
    font35 = TTF_OpenFont("arial.ttf", 35);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glClearColor(0, 0, 0, 0);
    glViewport(0, 0, windowWidth, windowHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, (GLdouble)windowWidth / (GLdouble)windowHeight, 0.1, 1000);
    SDL_GL_CreateContext(screen);

    gluOrtho2D(0, (GLdouble)windowWidth, 0, (GLdouble)windowHeight);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glClear(GL_COLOR_BUFFER_BIT);
    background = loadTexture("background.jpg");
    updateThread = thread(&update);
    updaterThread = thread(&updater);
    eventManager();
    // TODO: check new update when this one is finished
}

void size()
{
    SDL_GetWindowSize(screen, &windowWidth, &windowHeight);
}

void up()
{
    posY++;
    if(posY > 0)
    {
        posY--;
        return;
    }
    changeLog.pop_back();
    changeLog.push_front(changeLogTmp[-posY]);
    renderScreen();
}

void down()
{
    if(rendered != 0)
    {
        posY--;
        //cout << -posY << " " << changeLogTmp.size() - rendered - 1 << " " << changeLogTmp.size() << endl;
        if(-posY >= changeLogTmp.size() - rendered - 1)
        {
            posY++;
            return;
        }
        changeLog.pop_front();
        changeLog.push_back(changeLogTmp[-posY]);
    }
    renderScreen();
}

void manageUpdateLine()
{
    SDL_Surface *text = TTF_RenderText_Blended(font35, updateLine.c_str(), {255, 0, 0});
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GLuint textureTexte;
    glGenTextures(1, &textureTexte);
    glBindTexture(GL_TEXTURE_2D, textureTexte);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GLenum codagePixel;
    if(text->format->Rmask == 0x000000ff)
        codagePixel = GL_RGBA;
    else
    {
        #ifndef GL_BGRA
            #define GL_BGRA 0x80E1
        #endif
        codagePixel = GL_BGRA;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, 4, text->w, text->h, 0, codagePixel, GL_UNSIGNED_BYTE, text->pixels);
    double x2 = windowWidth / 50, x3 = windowWidth - windowWidth / 50, y2 = windowHeight / 67.5, y3 = windowHeight / 12, posX = windowWidth / 2, posY = windowHeight / 18, wDiv2 = text->w / 2, hDiv2 = text->h / 2, x0 = posX - wDiv2, x1 = posX + wDiv2, y0 = posY + hDiv2, y1 = posY - hDiv2;
    x0 = x0 < x2 ? x2 : x0;
    x1 = x1 > x3 ? x3 : x1;
    y1 = y1 < y2 ? y2 : y1;
    y0 = y0 > y3 ? y3 : y0;
    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2d(x0, y0);
        glTexCoord2i(0, 1); glVertex2d(x0, y1);
        glTexCoord2i(1, 1); glVertex2d(x1, y1);
        glTexCoord2i(1, 0); glVertex2d(x1, y0);
    glEnd();
}

void eventManager()
{
    bool opened = true;
    SDL_Event event;
    while(opened)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                {
                    opened = 0;
                    break;
                }
            case SDL_WINDOWEVENT: // TODO: when resized and at the bottom can do repetitive text
                if(event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    size();
                    renderScreen();
                }
                break;
            case SDL_MOUSEWHEEL:
                {
                    int y = event.wheel.y;
                    if(y == 1)
                        up();
                    else if(y == -1)
                        down();
                }
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_UP:
                        up();
                        break;
                    case SDLK_DOWN:
                        down();
                        break;
                }
            case SDL_MOUSEBUTTONDOWN: //patch
                if(isEnd)
                    free();
                renderScreen();
                break;
        }
    }
}

bool drawText(string str, bool title, int& a)
{
    if(str == "") return true;
    SDL_Color color = {100, 100, 100};
    if(title)
    {
        color = {0, 0, 0};
        TTF_SetFontStyle(font24, TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD);
    }
    SDL_Surface *text = TTF_RenderText_Blended(font24, str.c_str(), color);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GLuint textureTexte;
    glGenTextures(1, &textureTexte);
    glBindTexture(GL_TEXTURE_2D, textureTexte);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GLenum codagePixel;
    if(text->format->Rmask == 0x000000ff)
        codagePixel = GL_RGBA;
    else
    {
        #ifndef GL_BGRA
            #define GL_BGRA 0x80E1
        #endif
        codagePixel = GL_BGRA;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, 4, text->w, text->h, 0, codagePixel, GL_UNSIGNED_BYTE, text->pixels);
    double posX = text->w / 2 + windowWidth / 13, posY = text->h / 2 + (windowHeight - windowHeight / 4.4) - text->h * a, wDiv2 = text->w / 2, hDiv2 = text->h / 2, x0 = posX - wDiv2, x1 = posX + wDiv2, y0 = posY + hDiv2, y1 = posY - hDiv2;
    if(x1 > windowWidth - windowWidth / 15)
        x1 = windowWidth - windowWidth / 15;
    if(y1 < windowHeight / 5.2)
        return false;
    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2i(x0, y0);
        glTexCoord2i(0, 1); glVertex2i(x0, y1);
        glTexCoord2i(1, 1); glVertex2i(x1, y1);
        glTexCoord2i(1, 0); glVertex2i(x1, y0);
    glEnd();
    if(title)
        TTF_SetFontStyle(font24, TTF_STYLE_NORMAL);
    return true;
}

void renderScreen()
{
    if(rendering)
        return;
    rendering = true;
    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, background);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 0); glVertex2f(0, 0);
        glTexCoord2d(0, 1); glVertex2f(0, windowHeight);
        glTexCoord2d(1, 1); glVertex2f(windowWidth, windowHeight);
        glTexCoord2d(1, 0); glVertex2f(windowWidth, 0);
    glEnd();

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_TEXTURE_2D);
    glColor3ub(130, 200, 255);
    glBegin(GL_QUADS);
    double x0 = windowWidth / 250, x1 = windowWidth - windowWidth / 250, y0 = windowHeight / 168.75, y1 = windowHeight / 9 - windowHeight / 168.75, x2 = x0 + (x1 - x0) * progress / 100;
        glVertex2f(x0, y0);
        glVertex2f(x0, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y0);
    glEnd();
    glPopAttrib();

    for(int i = 1; i < changeLog.size() + 1; i++) // no unsigned
    {
        int first = (int)changeLog[i - 1][0];
        if(isAlphabetic(first))
            title = true;
        if(!drawText(replace(changeLog[i - 1], "\n", " "), title, i))
        {
            rendered = i - 2;
            break;
        }
        if(title)
            title = false;
    }

    manageUpdateLine();

    glFlush();
    SDL_GL_SwapWindow(screen);
    rendering = false;
}

void free()
{
    updaterThread.detach();
    updateThread.detach();
    TTF_Quit();
    SDL_Quit();
    exit(0);
}

SDL_Surface *flipSurface(SDL_Surface *surface)
{
    int pitch; // unsigned ?
    SDL_Surface *fliped_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, surface->w,surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);
    SDL_LockSurface(surface);
    SDL_LockSurface(fliped_surface);
    pitch = surface->pitch;
    for(unsigned int current_line = 0; current_line < surface->h; current_line++)
        memcpy(&((unsigned char*)fliped_surface->pixels)[current_line*pitch], &((unsigned char*)surface->pixels)[(surface->h - 1  - current_line)*pitch], pitch);
    SDL_UnlockSurface(fliped_surface);
    SDL_UnlockSurface(surface);
    return fliped_surface;
}

GLuint loadTexture(const char *filename)
{
    GLuint glID;
    SDL_Surface *picture_surface, *gl_surface, *gl_fliped_surface;
    Uint32 rmask, gmask, bmask, amask;
    picture_surface = IMG_Load(filename);
    if(picture_surface == NULL)
        return 0;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif
    SDL_PixelFormat format = *(picture_surface->format);
    format.BitsPerPixel = 32;
    format.BytesPerPixel = 4;
    format.Rmask = rmask;
    format.Gmask = gmask;
    format.Bmask = bmask;
    format.Amask = amask;
    gl_surface = SDL_ConvertSurface(picture_surface, &format, SDL_SWSURFACE);
    gl_fliped_surface = flipSurface(gl_surface);
    glGenTextures(1, &glID);
    glBindTexture(GL_TEXTURE_2D, glID);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, gl_fliped_surface->w, gl_fliped_surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, gl_fliped_surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(gl_fliped_surface);
    SDL_FreeSurface(gl_surface);
    SDL_FreeSurface(picture_surface);
    return glID;
}

size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

size_t writeData(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    if(downloadInit)
        amountDownloaded += size * nmemb;
    return fwrite(ptr, size, nmemb, stream);
}

string httpUrl(string url)
{
    return replaceAll(replaceAll(replaceAll(url, "%", "%25"), " ", "%20"), "`", "%60");
}

void downloadFileHttp(string url, string name, bool https) // could remove https as an argument and initialized it by calling a function
{
    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    if(https)
    {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
    }
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
    FILE *fp = fopen(name.c_str(), "wb");
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    fclose(fp);
}

void downloadFileInternet(string url, string name) /// TODO: replace ' ' with "%20"
{
    url = httpUrl(url);
    return downloadFileHttp(url, name, startsWith(url, httpsPrefix));
}

string getHttp(string url, bool https = false)
{
    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    if(https)
    {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
    }
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    string got;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &got);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return got;
}

string toString(vector<string> vec, string delimiter)
{
    string res = "";
    unsigned int vecSize = vec.size();
    for(unsigned int vecIndex = 0; vecIndex < vecSize; vecIndex++)
    {
        res += vec[vecIndex];
        if(vecIndex < vecSize - 1)
        {
            res += delimiter;
        }
    }
    return res;
}

string getInternet(string url)
{
    url = httpUrl(url);
    return getHttp(url, startsWith(url, httpsPrefix));
}
