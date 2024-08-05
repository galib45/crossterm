#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>

#define ARENA_IMPLEMENTATION
#include "arena.h"

static Arena arena = {0};
void* cr_alloc(size_t size) { return arena_alloc(&arena, size); }
void cr_free() { arena_free(&arena); }

void print_csi(const char *fmt, ...) {
    char *code = cr_alloc(20);
    va_list args; va_start(args, fmt);
    vsprintf(code, fmt, args);
    printf("\x1B[%s", code);
}

