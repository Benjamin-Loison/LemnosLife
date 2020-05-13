#ifndef BCRYPT_H_INCLUDED
#define BCRYPT_H_INCLUDED

#include <string>

int bcrypt_newhash(const char*, int, char*, size_t), bcrypt_checkpass(std::string/*const char**/, const char*);

#endif