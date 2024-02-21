all:
	windres icon.rc -O coff -o icon.res
	gcc main.c icon.res -o trashbin