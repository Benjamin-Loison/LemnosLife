#ifndef LANGUAGE_H_INCLUDED
#define LANGUAGE_H_INCLUDED

#define LANGUAGE_FILE_EXTENSION ".lang"

#include <string>
#include <vector>

void initializeLanguage(), loadLanguage(), loadAdditionalLanguage();
std::string lgd(std::string), lgServ(std::string), lgdForce(std::string id);
std::vector<std::string> lgd(std::vector<std::string> ids);

extern std::string languageFolder;

/// could make an external algorithm to get max size ?
#define lg(format, args...) \
    ({ \
        string a;\
        char buffer[2048]; \
        sprintf(buffer, lgd(format).c_str(), args); \
        a = buffer; \
        a; \
    })

#endif
