#pragma once

#include <assert.h>
#include <Windows.h>

#ifdef _DEBUG
#define SHOW_ERROR(text) {MessageBoxA(0, text, "에러", MB_OK); assert(false);}
#else
#define SHOW_ERROR(text) {}
#endif // DEBUG

#define SAFE_DELETE(p) if (p) {delete p; p = nullptr;}


// 게임 리터럴 상수
#define TILE_WIDTH 60.0f
#define TILE_HEIGHT 60.0f
#define MAX_SPEED_PER_FRAME 10.0f


