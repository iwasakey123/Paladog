#pragma once

#include "Types.h"
#include "Defines.h"
#include "Enums.h"

#include <Windows.h>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <assert.h>
#include <format>

using namespace std;

#define _CRTDEBUG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

