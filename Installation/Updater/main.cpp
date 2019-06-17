#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <gl.h>
#include <glu.h>
#include <string>
#include <thread>
#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <fstream>
#include <curl.h>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include "patch.h"
#include <deque>
#include <map>
#define lengthActualVersion 50
using namespace std;

char actualVersion[lengthActualVersion], pathSeparator;
SDL_Window *screen = 0;
TTF_Font *font24 = 0, *font35 = 0;
string getInternet(string), updateLine = "Chargement en cours...", fileDownload = "", versionDownload = "", unit = "", gameFolder = "", majFile = "MAJ.info", path = "", folder = "";
vector<string> maj, filesToDownload;
map<string, vector<string>> changeFilesVersion;
deque<string> changeLogTmp, changeLog;
thread updateThread, updaterThread;
double progress = 0, amountDownloaded = 0, amountToDownload = 0, unitDiv = 0;
void eventManager(), renderScreen(), updateManager(), free(), size(), launch(bool), downloadFileInternet(string, string), updateScreen();
int windowWidth = 0, windowHeight = 0, posY = 0, rendered = 0;
GLuint background = 0, loadTexture(const char*);
long getFileSize(string);
bool rendering = false, title = true, firstLaunch = false, needUpdate(), textInit = false, downloadInit = false, isEnd = false;

/*void openConsole()
{
    // TODO: console or not, every piece of information goes too in a file
    // TODO: select txt in the console
    int hConHandle;
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
    ios::sync_with_stdio();
    // TODO: colors ?
    // TODO: tab auto-completion http://www.cplusplus.com/forum/windows/58206/ https://msdn.microsoft.com/en-us/library/windows/desktop/ms682073(v=vs.85).aspx
}*/

// TODO: update this updater and add future updates

int main(int argc, char** argv) /// TODO: remove useless console
{
    // openConsole();
    pathSeparator =
    #ifdef _WIN32
        '\\';
    #else
        '/';
    #endif
    gameFolder = string("..") + pathSeparator + "Game" + pathSeparator;
    char psBuffer[128];
    FILE *pPipe;
    if((pPipe = _popen("cd", "rt")) == NULL)
        exit(1);
    fgets(psBuffer, 128, pPipe);
    for(int i = 0; i < 128; i++)
        if(psBuffer[i] == '\n')
            psBuffer[i] = '\0';
    _pclose(pPipe);
    path = psBuffer;
    if(!needUpdate())
        launch(true);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayMode DM;
    SDL_GetDesktopDisplayMode(0, &DM);
    windowWidth = 1365;
    windowHeight = 704;
    screen = SDL_CreateWindow(name.c_str(), 100, 100, windowWidth, windowHeight, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
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
    while (getline(ss, item, *delim))
        *(result++) = item;
}

vector<string> split(const string &s, const char *delim)
{
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}

string replace(string subject, const string& search, const string& replace)
{
    unsigned int pos = subject.find(search);
    if(pos > subject.length())
        return subject;
    return subject.replace(pos, search.length(), replace);
}

string convertDoubleToStr(double number)
{
    ostringstream convert;
    convert << number;
    return convert.str();
}

string convertIntToStr(int number)
{
    ostringstream convert;
    convert << number;
    return convert.str();
}

long convertStrToLong(string str)
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
    folder = folder.substr(0, folder.length());
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
    if(start)
        chgGameFolder();
    startup(string(path + "LemnosLife.exe").c_str());
    if(!start)
    {
        isEnd = true;
        updateScreen();
    }
    else
        exit(0);
}

bool needUpdate()
{
    // TODO: crypt content without homemade (compare local and server crypted version) /// THINK AGAIN AT THE SYSTEM (user knows version not crypted and can crypt himself or ask friends)
    maj = split(getInternet("https://lemnoslife.com/MAJ.txt"), "\n");
    FILE *majInfo = 0;
    short lengthActualDate = 17;
    char actualDate[lengthActualDate] = "";
    majInfo = fopen(majFile.c_str(), "r");
    if(majInfo == 0)
    {
        majInfo = fopen(majFile.c_str(), "w");
        string actualVersionTmp = "NeedUpdate", actualDateTmp = "00-00-0000#00-00";
        fputs(string(actualDateTmp + "\n" + actualVersionTmp).c_str(), majInfo);
        fclose(majInfo);
        for(unsigned int i = 0; i < actualVersionTmp.length(); i++)
            actualVersion[i] = actualVersionTmp[i];
        for(int i = 0; i < lengthActualDate; i++)
            actualDate[i] = actualDateTmp[i];
        firstLaunch = true;
        return true;
    }
    else
    {
        fgets(actualDate, lengthActualDate, majInfo);
        while(fgets(actualVersion, lengthActualVersion, majInfo) != NULL);
        fclose(majInfo);
        if(maj[0] != actualDate)
            return true;
        else
            return false;
    }
}

bool startsWith(string subject, string test)
{
    return !subject.compare(0, test.size(), test);
}

void updater()
{
    // TODO: if friends send files, find files like steam
    // TODO: delete system - instead of +
    map<unsigned int, string> versions;
    unsigned int version = 0;
    for(int i = 3; i < (int)maj.size(); i++)
        if(isAlphabetic(maj[i][0]))
        {
            if(startsWith(maj[i], actualVersion))
                break;
            changeFilesVersion[maj[i]] = split(replace(maj[i + 1], "+ ", ""), "&");
            for(int j = 0; j < (int)changeFilesVersion[maj[i]].size(); j++)
            {
                bool already = false;
                string doesFileNeedToBeDownload = changeFilesVersion[maj[i]][j];
                for(int k = 0; k < (int)filesToDownload.size(); k++)
                    if(doesFileNeedToBeDownload == filesToDownload[k])
                    {
                        already = true;
                        break;
                    }
                if(!already)
                {
                    filesToDownload.push_back(doesFileNeedToBeDownload);
                    versions[version] = convertIntToStr((int)changeFilesVersion[maj[i]].size()) + "@" + split(maj[i], " ")[0];
                    version++;
                }
            }
        }
    for(int i = 0; i < (int)filesToDownload.size(); i++)
       amountToDownload += getFileSize(filesToDownload[i]); // optimize multiples files (in php file)
    amountToDownload /= 1000; // converted in Ko (before in bytes)
    unit = "Ko";
    unitDiv = 1000;
    if(amountToDownload >= 1000)
    {
        amountToDownload /= 1000;
        unit = "Mo";
        unitDiv = 1000000;
    }
    if(amountToDownload >= 1000)
    {
        amountToDownload /= 1000;
        unit = "Go";
        unitDiv = 1000000000;
    }
    chgGameFolder();
    if(firstLaunch)
        CreateDirectory(gameFolder.c_str(), NULL);
    textInit = true;
    downloadInit = true;
    string url = "https://lemnoslife.com/MAJ/";
    char fileSeparator = 'A';
    unsigned int versionTmp = versions.size() - 1;
    int files = 0;
    versionDownload = split(versions[versionTmp], "@")[1];
    for(int i = (int)filesToDownload.size() - 1; i >= 0; i--) // TODO: unit downloaded adapted to the amount
    { // TODO: not right version displays each time (ex: AltisCraft.fr : first version)
        vector<string> elements = split(versions[versionTmp], "@");
        if(convertStrToInt(elements[0]) == files)
        {
            versionTmp--;
            versionDownload = elements[1];
            files = 0;
        }
        files++;
        unsigned int pos = filesToDownload[i].find_last_of(pathSeparator);
        if(pos > filesToDownload[i].length())
            pos = 0;
        fileDownload = filesToDownload[i].substr(pos, filesToDownload[i].length());
        renderScreen();
        string fileTmp = filesToDownload[i];
        if(filesToDownload[i].find('/') <= filesToDownload[i].length())
            fileSeparator = '/';
        else if(filesToDownload[i].find('\\') <= filesToDownload[i].length())
            fileSeparator = '\\';
        if(fileSeparator != 'A')
        {
            for(unsigned int j = 0; j < filesToDownload[i].length(); j++)
                if(filesToDownload[i][j] == fileSeparator)
                    filesToDownload[i][j] = pathSeparator;
            vector<string> folders = split(filesToDownload[i], string({pathSeparator, pathSeparator, '\0'}).c_str());
            unsigned int size = folders.size();
            string directory = folders[folders.size() - 1];
            if(directory.find(".") < directory.length())
                size--;
            folder = "";
            for(unsigned int i = 0; i < size; i++)
            {
                folder += folders[i] + pathSeparator;
                CreateDirectory(string(path + folder + pathSeparator).c_str(), NULL);
            }
        }
        downloadFileInternet(url + fileTmp, path + filesToDownload[i]);
    }
    FILE* update = 0;
    update = fopen(majFile.c_str(), "w+");
    fputs(string(maj[0] + "\n" + maj[1]).c_str(), update);
    fclose(update);
    launch(false);
}

void updateScreen()
{
    SDL_Event patch;
    patch.type = SDL_MOUSEBUTTONDOWN;
    SDL_PushEvent(&patch);
}

void update()
{
    while(1)
    {
        updateScreen();
        SDL_Delay(1000);
    }
}

void updateManager()
{
    font24 = TTF_OpenFont("arial.ttf", 24);
    font35 = TTF_OpenFont("arial.ttf", 35);

    for(int i = 3; i < (int)maj.size(); i++)
        if(maj[i][0] != '+')
            changeLog.push_back(maj[i] + "\n");
        else
            changeLog.push_back("\n");
    changeLogTmp = changeLog;
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
    posY--;
    if(rendered - posY + 1 > (int)changeLogTmp.size())
    {
        posY++;
        return;
    }
    changeLog.pop_front();
    changeLog.push_back(changeLogTmp[changeLog.size()]);
    renderScreen();
}

void manageUpdateLine()
{
    if(textInit)
    {
        progress = amountDownloaded * 100 / unitDiv / amountToDownload;
        updateLine = "Téléchargement en cours de " + fileDownload + " (" + versionDownload + ") : " + replace(convertDoubleToStr(progress), ".", ",").substr(0, 5) + " % (" + replace(convertDoubleToStr(amountDownloaded / unitDiv), ".", ",").substr(0, 5) + " " + unit + " / " + replace(convertDoubleToStr(amountToDownload), ".", ",").substr(0, 5) + " " + unit + ")";
    }
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
                    break;
                }
            case SDL_MOUSEWHEEL:
                {
                    int y = event.wheel.y;
                    if(y == 1)
                        up();
                    else if(y == -1)
                        down();
                    break;
                }
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

    for(int i = 1; i < (int)changeLog.size(); i++)
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
    // FreeConsole();
    updaterThread.detach();
    updateThread.detach();
    TTF_Quit();
    SDL_Quit();
    exit(0);
}

SDL_Surface *flipSurface(SDL_Surface *surface)
{
    int current_line,pitch;
    SDL_Surface *fliped_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, surface->w,surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);
    SDL_LockSurface(surface);
    SDL_LockSurface(fliped_surface);
    pitch = surface->pitch;
    for (current_line = 0; current_line < surface->h; current_line ++)
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
    gl_surface = SDL_ConvertSurface(picture_surface,&format,SDL_SWSURFACE);
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

void downloadFileHttp(string url, string name)
{
    CURL *curl = curl_easy_init();
    FILE *fp = fopen(name.c_str(), "wb");
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    fclose(fp);
}

void downloadFileHttps(string url, string name)
{
    CURL *curl = curl_easy_init();
    FILE *fp = fopen(name.c_str(), "wb");
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    fclose(fp);
}

void downloadFileInternet(string url, string name)
{
    string prefix = "https:";
    if(!url.compare(0, prefix.size(), prefix))
        return downloadFileHttps(url, name);
    else
        return downloadFileHttp(url, name);
}

long getFileSize(string url)
{
    CURL *curl = curl_easy_init();
    string got;
    curl_easy_setopt(curl, CURLOPT_URL, string("http://altiscraft.fr/size.php?f=MAJ/" + url).c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &got);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return convertStrToLong(got);
}

string getHttp(string url)
{
    CURL *curl = curl_easy_init();
    string got;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &got);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return got;
}

string getHttps(string url)
{
    CURL *curl = curl_easy_init();
    string got;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &got);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return got;
}

string getInternet(string url)
{
    string prefix = "https:";
    if(!url.compare(0, prefix.size(), prefix))
        return getHttps(url);
    else
        return getHttp(url);
}
