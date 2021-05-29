#ifndef LANGUAGE_H_INCLUDED
#define LANGUAGE_H_INCLUDED

#include <string>

void initializeLanguage();
std::string lgd(std::string, std::string);

#define lg(language, format, args...) \
    ({ \
        string a;\
        char buffer[2048]; \
        sprintf(buffer, lgd(language, format).c_str(), args); \
        a = buffer; \
        a; \
    })

extern std::string SOURCE_CODE_LANGUAGE;

#endif