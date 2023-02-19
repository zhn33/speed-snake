CC = gcc
CFLAGS = -lSDL2 -lSDL2_ttf -g 
INPUT = main.c
OUTPUT = -o snake

snake: main.o
	$(CC) $(CFLAGS) $(INPUT) $(OUTPUT)
