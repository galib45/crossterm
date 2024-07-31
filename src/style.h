// Define the enum for color types
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

// Define a struct to hold RGB values
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB;

// Define a union to hold either RGB values or ANSI value
typedef union {
    RGB rgb;
    uint8_t ansi_value;
} ColorData;

// Define a struct to represent the Color with its type and data
typedef struct {
    ColorType type;
    ColorData data;
} Color;

typedef struct {
    Color foreground;
    Color background;
    char *text;
} StyledContent;

void set_foreground_color(Color color) {
    char *code = cr_alloc(10); RGB rgb;
    switch (color.type) {
        case COLOR_RESET: print_csi("39m"); break;
        case COLOR_BLACK: print_csi("30m"); break;
        case COLOR_DARK_RED: print_csi("31m"); break;
        case COLOR_DARK_GREEN: print_csi("32m"); break;
        case COLOR_DARK_YELLOW: print_csi("33m"); break;
        case COLOR_DARK_BLUE: print_csi("34m"); break;
        case COLOR_DARK_MAGENTA: print_csi("35m"); break;
        case COLOR_DARK_CYAN: print_csi("36m"); break;
        case COLOR_GREY: print_csi("37m"); break;
        case COLOR_DARK_GREY: print_csi("90m"); break;
        case COLOR_RED: print_csi("91m"); break;
        case COLOR_GREEN: print_csi("92m"); break;
        case COLOR_YELLOW: print_csi("93m"); break;
        case COLOR_BLUE: print_csi("94m"); break;
        case COLOR_MAGENTA: print_csi("95m"); break;
        case COLOR_CYAN: print_csi("96m"); break;
        case COLOR_WHITE: print_csi("97m"); break;
        case COLOR_ANSI_VALUE:
            sprintf(code, "38;5;%um", color.data.ansi_value);
            print_csi(code);
            break;
        case COLOR_RGB:
            rgb = color.data.rgb;
            sprintf(code, "38;2;%u;%u;%um", rgb.r, rgb.g, rgb.b);
            print_csi(code);
            break;
    }
}

void reset_style() {
    print_csi("0m");
}

void print_styled_content(StyledContent *content) {
    if (!content->text) return;
    set_foreground_color(content->foreground);
    printf("%s", content->text);
    reset_style();
}

StyledContent* sc(char *text) {
    StyledContent *content = cr_alloc(sizeof(StyledContent));
    content->text = strdup(text);
    return content;
}

StyledContent* with(StyledContent *content, ColorType type) {
    content->foreground.type = type;
    return content;
}

StyledContent* with_rgb(StyledContent *content, uint8_t r, uint8_t g, uint8_t b) {
    content->foreground.type = COLOR_RGB;
    RGB rgb = {.r = r, .g = g, .b = b};
    content->foreground.data.rgb = rgb;
    return content;
}

StyledContent* with_ansi(StyledContent *content, uint8_t ansi_value) {
    content->foreground.type = COLOR_ANSI_VALUE;
    content->foreground.data.ansi_value = ansi_value;
    return content;
}

StyledContent* with_black(StyledContent *c) { return with(c, COLOR_BLACK); }
StyledContent* with_red(StyledContent *c) { return with(c, COLOR_RED); }
StyledContent* with_green(StyledContent *c) { return with(c, COLOR_GREEN); }
StyledContent* with_yellow(StyledContent *c) { return with(c, COLOR_YELLOW); }
StyledContent* with_blue(StyledContent *c) { return with(c, COLOR_BLUE); }
StyledContent* with_magenta(StyledContent *c) { return with(c, COLOR_MAGENTA); }
StyledContent* with_cyan(StyledContent *c) { return with(c, COLOR_CYAN); }
StyledContent* with_white(StyledContent *c) { return with(c, COLOR_WHITE); }
