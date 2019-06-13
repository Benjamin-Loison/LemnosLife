#include "Scanner.h"
using namespace std;

Scanner::Scanner(string path)
{
    m_fileStream.open(path);
}

string Scanner::nextLine()
{
    string line;
    getline(m_fileStream, line);
    return line;
}
