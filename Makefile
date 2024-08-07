CC = clang
AR = ar
CFLAGS = -Wall -Wextra
LDFLAGS =

# Default target: Build static library
all: run

run: test
	bin/test

test: test/test.c
	$(CC) $(CFLAGS) -o bin/test test/test.c -Iinclude -Llib -lcrossterm

posix: common_objects posix_objects | dirs
	$(AR) rcs lib/libcrossterm.a build/*.o
	cp src/crossterm.h include/

windows: common_objects windows_objects | dirs
	$(AR) rcs lib/libcrossterm.a build/*.o
	cp src/crossterm.h include/

# Rule to compile common source files into object files
common_objects: $(COMMON_SOURCES) | dirs
	$(CC) $(CFLAGS) -c src/arena.c -o build/arena.o
	$(CC) $(CFLAGS) -c src/style.c -o build/style.o
	$(CC) $(CFLAGS) -c src/common.c -o build/common.o
	$(CC) $(CFLAGS) -c src/crossterm.c -o build/crossterm.o

windows_objects: src/windows.c | dirs
	$(CC) $(CFLAGS) -c src/windows.c -o build/windows.o

posix_objects: src/posix.c | dirs
	$(CC) $(CFLAGS) -c src/posix.c -o build/posix.o

dirs:
	mkdir -p bin build include lib

clean:
	rm -rf bin build include lib

.PHONY: all posix windows clean test
