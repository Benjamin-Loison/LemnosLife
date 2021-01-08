#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#define DIGITS "0123456789"
// DIGITS doesn't seem to be used
#define DIGITS_EXTENDED "0123456789.,"
#define DIGITS_AND_OPERATORS "0123456789.-+"
// use variables instead of constants ?
///#define BASIC_CHARS_WITHOUT_SPACE_BAR "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\";#$%&'()*+,-./:;<=>?@[]^_`{|}~"
#define ALPHABET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define GUI_STRUCTURES_FILTER "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-,. _"

#include <string>

void initializeInput(), freeInput(), eventManager(), setClipboard(const std::string&), sendChat(std::string, bool = false);
extern bool /*mouse[5], */clicked, opened, isLeftKeyPressed, isRightKeyPressed, isForwardKeyPressed, isBackwardKeyPressed, isRotatingRightKeyPressed, isRotatingLeftKeyPressed, isHelicopterIncreaseKeyPressed, isHelicopterDecreaseKeyPressed; // should make a more general system (caution to return or continue like instructions)
std::string getClipboard();
extern unsigned long long pingTime;
bool isPressed(long long), isTyping();
extern int mouseX, mouseY;
extern double testDouble;
//enum NEED_MOUSE_ACTION {NMA_NO, NMA_ENABLE, NMA_DISABLE};
//NEED_MOUSE_ACTION gameWindowMouseActionNeed;

#endif
