#pragma once

// 매크로 정의
#include "define.h"

// Windows API
#include <Windows.h>

// std
#include <cmath>
#include <string>
#include <typeinfo>
#include <memory>

using std::string;

// stl, 헤더파일에서 사용시 stdafx.h를 다시 인클루드
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <vector>

using std::shared_ptr;
using std::priority_queue;
using std::unordered_map;
using std::unordered_set;
using std::unordered_multiset;
using std::vector;

// Base
#include "KmBase/Vector.h"


int VectorToTileIndex(FVector2D Vector);
float VectorToRenderPriority(FVector2D Vector);
FVector2D TileIndexToVector(int nTileIndex);