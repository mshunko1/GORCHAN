// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"

typedef std::wstring gstring;
typedef std::int64_t gint;
typedef std::wofstream gofstream;
typedef std::wifstream gifstream;
typedef std::int64_t shape_index;
typedef std::locale glocale;
typedef std::experimental::filesystem::path gfs_path;
typedef gstring gguid;


#define BASE_PATH gfs_path(L"memory")

#include "base_shape.h"
#include "ls_memory.h"
#include "rule.h"
#include "linker.h"

#endif //PCH_H
