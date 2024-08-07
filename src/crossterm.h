#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>

#define REGION_DEFAULT_CAPACITY 8192

typedef struct Region Region;
typedef struct Arena Arena;

struct Region {
    Region *next;
    size_t count;
    size_t capacity;
    uintptr_t data[];
};

struct Arena {
    Region *begin, *end;
};

typedef enum {
    COLOR_RESET,
    COLOR_BLACK, COLOR_DARK_GREY,
    COLOR_RED, COLOR_DARK_RED,
    COLOR_GREEN, COLOR_DARK_GREEN,
    COLOR_YELLOW, COLOR_DARK_YELLOW,
    COLOR_BLUE, COLOR_DARK_BLUE,
    COLOR_MAGENTA, COLOR_DARK_MAGENTA,
    COLOR_CYAN, COLOR_DARK_CYAN,
    COLOR_WHITE, COLOR_GREY,
    COLOR_RGB,
    COLOR_ANSI_VALUE
} ColorType;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB;

typedef union {
    RGB rgb;
    uint8_t ansi_value;
} ColorData;

typedef struct {
    ColorType type;
    ColorData data;
} Color;

typedef struct {
    Color foreground;
    Color background;
    char *text;
} StyledContent;

void *arena_alloc(Arena *a, size_t bytes);
void arena_free(Arena *a);
void* cr_alloc(size_t size);
void cr_free();
void errmsg(const char *format, ...);
void setup();
void cleanup();
void print_csi(const char *fmt, ...);
void move_to(uint8_t x, uint8_t y);
void enter_alternate_screen();
void leave_alternate_screen();
void set_foreground_color(Color color);
void reset_style();
void print_styled_content(StyledContent *content);
StyledContent* sc(char *text);
StyledContent* with(StyledContent *content, ColorType type);
StyledContent* with_rgb(StyledContent *content, uint8_t r, uint8_t g, uint8_t b);
StyledContent* with_ansi(StyledContent *content, uint8_t ansi_value);
StyledContent* with_black(StyledContent *c);
StyledContent* with_red(StyledContent *c);
StyledContent* with_green(StyledContent *c);
StyledContent* with_yellow(StyledContent *c);
StyledContent* with_blue(StyledContent *c);
StyledContent* with_magenta(StyledContent *c);
StyledContent* with_cyan(StyledContent *c);
StyledContent* with_white(StyledContent *c);
