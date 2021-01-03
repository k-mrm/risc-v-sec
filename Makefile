CC := gcc
CFLAGS = -Wall -Wextra -I ./include/ -Og -g #-DNDEBUG
SRCROOT = ./src
SRCDIRS := $(shell find $(SRCROOT) -type d)
SRCS=$(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))
OBJS=$(SRCS:.c=.o)
PROGRAM = risc-v-sec
.SUFFIXES: .c .o
.PHONY: clean

risc-v-sec: $(OBJS)
	$(CC) -o $@ $^

clean:
	$(RM) $(OBJS) $(PROGRAM)
