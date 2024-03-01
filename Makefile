.PHONY: all clean
.SUFFIXES:
.SUFFIXES: .c .rc .o .res

WINDRES=windres
CC=gcc

all: trashbin.exe

trashbin.exe: main.o resource.res
	$(CC) -o $@ main.o resource.res -mwindows -municode

.c.o:
	$(CC) -DUNICODE -D_UNICODE -o $@ -c $<

.rc.res:
	$(WINDRES) -O coff -o $@ $<

clean:
	-rm -f *.o *.res *.exe
