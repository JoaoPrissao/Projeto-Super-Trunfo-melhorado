CC = gcc
CFLAGS = -Wall
SRC = main.c src/cartas.c src/io.c src/utils.c src/jogo.c
INCLUDE = -Iinclude
OUTPUT = supertrunfo

all: $(OUTPUT)

$(OUTPUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(INCLUDE) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT)
