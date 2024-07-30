#include "common.h"

#if defined(_WIN32) || defined(_WIN64)
    #include "winapi.h"
#else
    #include "posix.h"
#endif
