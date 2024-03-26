# Makefile for myFind

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic

# Targets
all: myFind

myfind: myfind.c
	$(CC) $(CFLAGS) -o myFind myFind.c

clean:
	rm -f myFind

