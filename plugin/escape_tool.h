#pragma once

#include "plugin.h"

char* utf8ToEscapedStr(char* from);
ParadoxTextObject* utf8ToEscapedStr2(ParadoxTextObject* from);
char* escapedStrToUtf8(ParadoxTextObject* from);
char* utf8ToEscapedStr3(char* from);
errno_t convertWideTextToEscapedText(const wchar_t* from, char** to);
errno_t convertEscapedTextToWideText(const std::string* from, std::wstring* to);
