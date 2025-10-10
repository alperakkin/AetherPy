CC := gcc

CFLAGS := -Wall -g -I/Users/alperakkin/.pyenv/versions/3.12.11/include/python3.12 -Isrc/libs
LDFLAGS := -L/Users/alperakkin/.pyenv/versions/3.12.11/lib -lpython3.12 -undefined dynamic_lookup

SRC := src/main.c src/game.c src/engine.c src/scripting.c src/utils.c
OBJ := $(patsubst src/%.c,build/%.o,$(SRC))
TARGET := bin/game

all: $(TARGET)


$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)
