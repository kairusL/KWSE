//------------------------ Common is a header that would gonna be using for inside of the project and outside of the project -------------------------------//
//------------------------ Eyeryone that using my library also need to know about Core, So under Core include Common.h.      -------------------------------//
//------------------------ If I need something within it then outside people need it but outside people only use Core.h      -------------------------------//
//------------------------ So you need to include Common.h under so outside people see Common                                -------------------------------//


#pragma once  

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

//Win32 headers
#include <objbase.h>
#include <Windows.h>

//Standard headers
#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <filesystem>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>