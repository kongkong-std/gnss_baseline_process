# makefile for adjustment of gnss network
CC = gcc
CFLAGS = -Wall -g -c
PATH_SRC = ../src
OBJECT := $(patsubst %.c,%.o,$(wildcard $(PATH_SRC)/*.c))

.PHONY: all clean

all: baseline_exe

baseline_exe: $(OBJECT)
	$(CC) $(OBJECT) -o baseline_exe -lm

%.o: %.c
	$(CC) $(CFLAGS) "$<" -o "$@"

clean:
	rm baseline_exe $(OBJECT)
