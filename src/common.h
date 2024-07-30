#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

void errmsg(const char *format, ...) {
    va_list args;
    va_start(args, format);
	fprintf(stderr, "[ERROR] ");
    vfprintf(stderr, format, args);
	fprintf(stderr, "\n");
    va_end(args);
    exit(EXIT_FAILURE);
}
