#
# Makefile
# antoine, 2017-09-03 16:33
#

.PHONY: penny clean

CC = gcc
LEX = flex
YACC = yacc
CFLAGS = -Wall -O3

SRCS = $(shell find src -type f -name '*.c')
OBJS += bin/parser.o bin/lexer.o
OBJS += $(SRCS:src/%.c=bin/%.o)

penny: build

pre_build:
	mkdir -p bin

build: pre_build $(OBJS)
	gcc -ll -ly -o bin/penny $(OBJS)

clean:
	rm -rf bin

bin/lexer.o: src/lexer.lex
	$(LEX) -o $(@:.o=.c) $<
	$(CC) -Iinclude -Ibin -c -o $@ $(@:.o=.c)

bin/parser.o: src/parser.y
	$(YACC) -d -o $(@:.o=.c) $<
	$(CC) -Iinclude -Ibin -c -o $@ $(@:.o=.c)

bin/%.o: src/%.c
	$(CC) $(CFLAGS) -Iinclude -Ibin -c -o $@ $<

# vim:ft=make
#
