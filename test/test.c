#include <stdio.h>
#include "crossterm.h"

int main() {
    setup();
    print_styled_content(with_red(sc("kiri\r\n")));
    print_styled_content(with_green(sc("kilrim\r\n")));
    print_styled_content(with_rgb(sc("kilrim\r\n"), 0, 0, 255));
    cleanup();
    return 0;
}
