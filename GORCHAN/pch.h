// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"

class rule;

typedef std::wstring gstring;
typedef std::int64_t gint;
typedef std::wofstream gofstream;
typedef std::wifstream gifstream;
typedef std::int64_t shape_index;
typedef std::locale glocale;
typedef std::experimental::filesystem::path gfs_path;
namespace gfs = std::experimental::filesystem;
typedef gstring gguid;
#ifndef _WINDOWS
typedef std::thread gthread;
#endif
template<class T> using gvector = std::vector<T>;   
template<class T1, class T2> using gmap = std::map<T1, T2>;
template<class T1, class T2> using gpair = std::pair<T1,T2>;
template<class T> using gqueue = std::queue<T>;
template<class T1, class T2, class T3> using grule_queue = std::priority_queue<T1, T2, T3>;

#define gto_gstring(x) std::to_wstring(x)
#define BASE_PATH gfs_path(L"C:/dev/Mind")
#define LINKS_OUT   6
#define LINKS_IN    6

#include "rule.h"
#include "link.h"
#include "lib/gexception.h"
#include "lib/indexator.h"
#include "base_shape.h"
#include "fona_shape.h"
#include "eos_shape.h"
#include "whois_shape.h"
#include "howis_shape.h"
#include "soul_matter_shape.h"
#include "ls_memory.h"
#include "linker.h"
#include "bg_context.h"
#include "shape_iterator.h"
#include "ear.h"


#endif //PCH_H
