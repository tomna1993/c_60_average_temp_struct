CC := gcc
#CFLAGS := 
DEST := ./build/

all: average_temp.c
	mkdir -p build
	$(CC) average_temp.c -lcs50 -o $(DEST)/average_temp 