default: all

CC=emcc
CCFLAGS=-O3 -Iinclude -Wall -Wno-incompatible-function-pointer-types

test: bin/ffi.o bin/main.o bin/ffi_call.o
	$(CC) $(CCFLAGS) bin/ffi.o bin/ffi_call.o bin/main.o -o test

bin/ffi.o: src/ffi.c
	mkdir -p bin
	$(CC) $(CCFLAGS) -c src/ffi.c -o bin/ffi.o

bin/ffi_call.o: src/ffi_call.c
	mkdir -p bin
	$(CC) $(CCFLAGS) -c src/ffi_call.c -o bin/ffi_call.o

bin/main.o: src/main.c
	mkdir -p bin
	$(CC) $(CCFLAGS) -c src/main.c -o bin/main.o

clean:
	rm -rf bin

all: test
.PHONY: all clean