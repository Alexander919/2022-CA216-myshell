CC 					= gcc
CFLAGS 			= -std=c89 -Wall -Wextra -Wpedantic -g
CPPFLAGS 		= -Iinclude

TARGET 			= build/myshell
TOK_TARGET 	= build/tok

TOK_SRCS 		= src/tokenizer.c src/util.c
# TOK_OBJS 		= $(TOK_SRCS:.c=.o)
TOK_OBJS 		= $(patsubst src/%.c,build/%.o,$(TOK_SRCS))

SRCS 				= src/main.c src/util.c
# SRCS 				= $(wildcard src/*.c)
# OBJS 				= $(SRCS:.c=.o)
OBJS 				= $(patsubst src/%.c,build/%.o,$(SRCS))

LDFLAGS 		=
LDLIBS 			=

.PHONY: all tok clean run run_tok

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

tok: $(TOK_TARGET)

run_tok: $(TOK_TARGET)
	./$(TOK_TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(TOK_TARGET): $(TOK_OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

build/util.o: include/util.h

build:
	mkdir -p build

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f $(TOK_OBJS) $(TOK_TARGET)
