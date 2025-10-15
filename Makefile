CC := gcc

CFLAGS := -Wall -g -I/Users/alperakkin/.pyenv/versions/3.12.11/include/python3.12 -Isrc/include
LDFLAGS := -L/Users/alperakkin/.pyenv/versions/3.12.11/lib -lpython3.12 -undefined dynamic_lookup -flat_namespace



SRC := $(wildcard src/*.c src/game/*.c src/libs/*.c)
OBJ := $(patsubst src/%,build/%,$(SRC:.c=.o))
BUILD_DIRS := $(sort $(dir $(OBJ)))
TARGET := bin/game

all: $(TARGET)


$(TARGET): $(OBJ)
	@mkdir -p $(dir $@)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIRS):
	mkdir -p $@

build/%.o: src/%.c | $(BUILD_DIRS)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf build $(TARGET)
