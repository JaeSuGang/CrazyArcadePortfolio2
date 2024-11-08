#pragma once

#include <assert.h>
#include <Windows.h>

#ifdef _DEBUG
#define SHOW_ERROR(text) {MessageBoxA(0, text, "¿¡·¯", MB_OK); assert(false);}
#else
#define SHOW_ERROR(text) {}
#endif // DEBUG

#define SAFE_DELETE(p) if (p) {delete p; p = nullptr;}

