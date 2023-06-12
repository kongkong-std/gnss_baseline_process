# makefile for adjustment of gnss network
CC = gcc
CFLAGS = -Wall -g -c
PATH_SRC = ../src
OBJECT := $(patsubst %.c,%.o,$(wildcard $(PATH_SRC)/*.c))

.PHONY: all clean

all: adjust_exe

adjust_exe: $(OBJECT)
	$(CC) $(OBJECT) -o adjust_exe -lm

%.o: %.c
	$(CC) $(CFLAGS) "$<" -o "$@"

clean:
	rm adjust_exe $(OBJECT)
