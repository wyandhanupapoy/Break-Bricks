CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LIBS = `sdl2-config --libs`  # Mendapatkan library SDL2 secara otomatis
INCLUDES = `sdl2-config --cflags`  # Mendapatkan header SDL2

SRC = main.c
OBJ = $(SRC:.c=.o)
TARGET = brickbreaker

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBS)

clean:
	rm -f $(OBJ) $(TARGET)
