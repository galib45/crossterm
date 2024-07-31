#include <stdio.h>
#include "crossterm.h"

int main() {
    setup();
    print_styled_content(with_red(sc("kiri\n")));
    print_styled_content(with_green(sc("kilrim\n")));
    print_styled_content(with_rgb(sc("kilrim"), 0, 0, 255));
    cleanup();
    return 0;
}
