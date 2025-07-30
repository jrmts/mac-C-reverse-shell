CC = clang
CFLAGS = -Wall -Wextra -g -Iinclude
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
OUT = build/reverse_shell

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(SRC)

clean:
	rm -rf build/*