CFLAGS := -Wall -Wextra
all: main.pp main
main: main.c ConfigIni.c ConfigFormat.c ConfigFormat.h ConfigFormatGen.h ConfigStructs.h
	cc $(CFLAGS) -o $@ main.c ConfigIni.c ConfigFormat.c
main.pp: main.c ConfigFormat.h ConfigFormatGen.h ConfigStructs.h
	cc $(CFLAGS) -E main.c > $@
