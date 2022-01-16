#include <cstdarg>
#include "debug.h"

#ifndef DEBUG
int dprintf(const char* format, ...)
{
    return 0;
}
#endif
