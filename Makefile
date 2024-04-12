CC=clang
EXEC=build/chip8_c
CCFLAGS=-Wall -Werror -Wextra -std=c99 $(shell pkg-config --cflags SDL2) -Iinclude
LDFLAGS=$(shell pkg-config --libs SDL2)
SRC=$(shell find src -name '*.c')
OBJ=$(SRC:src/%.c=build/%.o)

.PHONY: all clean run

all: $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(EXEC)

run: all
	./$(EXEC)

build/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) -c $< -o $@

build/:
	mkdir -p $@

clean:
	rm -f -r build