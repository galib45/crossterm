#include "crossterm.h"

void move_to(uint8_t x, uint8_t y) { print_csi("%u;%uH", y+1, x+1); }
void enter_alternate_screen() { print_csi("?1049h"); }
void leave_alternate_screen() { print_csi("?1049l"); }
