.SUFFIXES:
.SUFFIXES: .c .rc .o .res

WINDRES=windres
CC=gcc

all: trashbin.exe

trashbin.exe: main.o resource.res
	$(CC) -o $@ main.o resource.res

.c.o:
	$(CC) -o $@ -c $<

.rc.res:
	$(WINDRES) -O coff -o $@ $<

