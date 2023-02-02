#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
// Windows Header Files
#ifdef WINDOWS
#include <windows.h>
#endif

#include <locale>
#include <iomanip>
#include <codecvt>
#include <cstdint>
#include <string>
#include <thread>
#include <mutex>
#include <iostream>
#include <fstream>
#include <map>
#include <experimental/filesystem>
