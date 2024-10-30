#pragma once

#include <assert.h>
#include <algorithm>
#include <cctype>
#include <Windows.h>

#ifdef _DEBUG
#define SHOW_ERROR(text) {MessageBoxA(0, text, "¿¡·¯", MB_OK); assert(false);}
#else
#define SHOW_ERROR(text) {}
#endif // DEBUG

#define SAFE_DELETE(p) if (p) {delete p; p = nullptr;}

#define LOWER_STRING(str) std::transform(str.begin(), str.end(), str.begin(), [](char c){return std::tolower(c);});