#pragma once

#include "plugin.h"

char* utf8ToEscapedStr(char* from);
PString* utf8ToEscapedStr2(PString* from);
char* escapedStrToUtf8(PString* from);
char* utf8ToEscapedStr3(char* from);
PString* escapedStrToUtf8A(PString* from);
errno_t convertWideTextToEscapedText(const wchar_t* from, char** to);
errno_t convertEscapedTextToWideText(const std::string* from, std::wstring* to);
