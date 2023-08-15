default: staticlib

CC=emcc
AR=emar
CCFLAGS=-O3 -Iinclude -Wall -Wno-incompatible-function-pointer-types

bin/example: bin/ffi.o bin/example.o bin/ffi_call.o
	mkdir -p bin
	$(CC) $(CCFLAGS) bin/ffi.o bin/ffi_call.o bin/example.o -o bin/example

bin/ffi.o: src/ffi.c
	mkdir -p bin
	$(CC) $(CCFLAGS) -c src/ffi.c -o bin/ffi.o

src/ffi_call.c: src/ffi_call.c.template
	python3 generateImpl.py $(MAX_NUM_ARGS)

bin/ffi_call.o: src/ffi_call.c
	mkdir -p bin
	$(CC) $(CCFLAGS) -c src/ffi_call.c -o bin/ffi_call.o

bin/example.o: src/example.c
	mkdir -p bin
	$(CC) $(CCFLAGS) -c src/example.c -o bin/example.o

bin/libffi.a: bin/ffi.o bin/ffi_call.o
	mkdir -p bin
	emar rcs bin/libffi.a bin/ffi.o bin/ffi_call.o

clean:
	rm -rf bin src/ffi_call.c

example: bin/example
staticlib: bin/libffi.a

all: example staticlib
.PHONY: all clean example staticlib