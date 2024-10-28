#pragma once

#include <assert.h>
#include <Windows.h>

#ifdef _DEBUG
#define MSG_ASSERT(text) MessageBoxA(0, text, "¿¡·¯", MB_OK); assert(false) 
#else
#define MSG_ASSERT(text) (void(0))
#endif // DEBUG
