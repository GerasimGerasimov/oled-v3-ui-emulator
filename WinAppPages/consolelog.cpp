#include "consolelog.h"

HWND console::hwnd = NULL;

void console::log(std::wstring text) {
    int strLen = SendMessage(hwnd, WM_GETTEXTLENGTH, 0, 0);
    SendMessage(hwnd, EM_SETSEL, (WPARAM)strLen, (LPARAM)strLen);    
    SendMessage(hwnd, EM_REPLACESEL, (WPARAM)FALSE, (LPARAM)text.c_str());
}

//How convert std::string to std::wstring in C++?
//std::string str("Hello world!");
//std::wstring wstr(str.begin(), str.end());