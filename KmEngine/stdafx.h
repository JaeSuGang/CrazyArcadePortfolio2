#pragma once

// 매크로 정의
#include "define.h"

// Windows API
#include <Windows.h>

// std
#include <string>
#include <typeinfo>

using std::string;

// stl은 템플릿과 관련해서 계속 오류가 나므로 헤더파일에선 직접 인클루드 시키기
#include <unordered_map>

using std::unordered_map;
