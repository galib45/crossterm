#include <unistd.h>
#include <termios.h>
struct termios orig_termios;

void enable_mouse_reporting() {
    print_csi("?1003h");
    print_csi("?1006h");
    print_csi("?1015h");
}

void enable_raw_mode() {
    struct termios new_termios;
    new_termios = orig_termios;
    cfmakeraw(&new_termios);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void cleanup() {
    cr_free();
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

void pl_exit(int exit_code) {
    cleanup();
    exit(exit_code);
}

void errmsg(const char *format, ...) {
    va_list args;
    va_start(args, format);
	fprintf(stderr, "[ERROR] ");
    vfprintf(stderr, format, args);
	fprintf(stderr, "\n");
    va_end(args);
    pl_exit(EXIT_FAILURE);
}

poll_event(int timeout) {

}

void setup() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    enable_raw_mode();
}

