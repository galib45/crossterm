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

    // INPUT_RECORD ir; KEY_EVENT_RECORD ker;
    // bool should_run = true;
    // while(should_run) {
    //     ir = poll_event(500);
    //     if (ir.EventType == KEY_EVENT) {
    //         ker = ir.Event.KeyEvent;
    //         if (ker.bKeyDown) {
    //             switch (ker.uChar.UnicodeChar) {
    //                 case 'q': should_run = false; break;
    //                 default: printf("%d\n", ker.uChar.UnicodeChar); break;
    //             }
    //         }
    //     }
    // }

