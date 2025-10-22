CC := gcc


GFX_FLAGS := -L/usr/local/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

PYTHON_INCLUDE := -I/Users/alperakkin/.pyenv/versions/3.12.11/include/python3.12
PYTHON_LIB := -L/Users/alperakkin/.pyenv/versions/3.12.11/lib -lpython3.12


CFLAGS := -Wall -g $(PYTHON_INCLUDE) -Isrc/include
LDFLAGS := $(PYTHON_LIB) $(GFX_FLAGS) -undefined dynamic_lookup -flat_namespace

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

.PHONY: all clean
