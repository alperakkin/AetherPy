CC := gcc

CFLAGS := -Wall -g -I/Users/alperakkin/.pyenv/versions/3.12.11/include/python3.12
LDFLAGS := -L/Users/alperakkin/.pyenv/versions/3.12.11/lib -lpython3.12 -undefined dynamic_lookup

SRC := src/main.c src/engine.c
OBJ := $(patsubst src/%.c,build/%.o,$(SRC))
TARGET := bin/game

all: $(TARGET)

# Build klasörü varsa kullan, yoksa oluştur
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)
