#include <stdbool.h>
#include <windows.h>

HANDLE hIn, hOut;
DWORD dwOriginalOutMode = 0, dwOriginalInMode = 0;

void pl_exit(int exit_code) {
    SetConsoleMode(hIn, dwOriginalInMode);
    SetConsoleMode(hOut, dwOriginalOutMode);
    ExitProcess(exit_code);
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

void poll_events(DWORD timeout) {
    DWORD result, cNumRead;
    INPUT_RECORD irInBuf[128];
    while (true) {
        result = WaitForSingleObject(hIn, timeout);
        if (result == WAIT_TIMEOUT) continue;
        else if (result == WAIT_FAILED) errmsg("Failed to wait for event.");
        else break;
    }
    if (!ReadConsoleInput(hIn, irInBuf, 128, &cNumRead)) errmsg("Failed to read console input.");
}

void setup() {
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) errmsg("Couldn't get standard output handle");
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    if (hIn == INVALID_HANDLE_VALUE) errmsg("Couldn't get standard input handle");

    DWORD dwOriginalOutMode = 0;
    DWORD dwOriginalInMode = 0;
    if (!GetConsoleMode(hOut, &dwOriginalOutMode)) errmsg("Couldn't get output mode");
    if (!GetConsoleMode(hIn, &dwOriginalInMode)) errmsg("Couldn't get output mode");

    DWORD dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
    DWORD dwRequestedInModes = ENABLE_VIRTUAL_TERMINAL_INPUT | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;

    DWORD dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
    if (!SetConsoleMode(hOut, dwOutMode))
    {
        // we failed to set both modes, try to step down mode gracefully.
        dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
        if (!SetConsoleMode(hOut, dwOutMode)) errmsg("Failed to set VT output mode");
    }

    DWORD dwInMode = dwOriginalInMode | dwRequestedInModes;
    if (!SetConsoleMode(hIn, dwInMode)) errmsg("Failed to set VT input mode");
}
