#include <stdio.h>
#include "crossterm.h"

int main() {
    setup_terminal();
    printf("\x1B[31mHello, World!\x1B[0m");
    return 0;
}
