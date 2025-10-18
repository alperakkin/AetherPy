CC := gcc

CFLAGS := -Wall -g -I/Users/alperakkin/.pyenv/versions/3.12.11/include/python3.12 -Isrc/include `sdl2-config --cflags`
LDFLAGS := -L/Users/alperakkin/.pyenv/versions/3.12.11/lib -lpython3.12 -undefined dynamic_lookup -flat_namespace `sdl2-config --libs`

SRC := $(shell find src -name '*.c')
OBJ := $(patsubst src/%,build/%,$(SRC:.c=.o))
BUILD_DIRS := $(sort $(dir $(OBJ)))
TARGET := bin/Aether

all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)


build/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf build $(TARGET)
