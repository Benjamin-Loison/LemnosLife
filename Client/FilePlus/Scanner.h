#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <fstream>

class Scanner
{
    public:
        Scanner(), Scanner(const Scanner &), Scanner(std::string);
        std::string nextLine();
    private:
        std::ifstream m_fileStream;
};

#endif
