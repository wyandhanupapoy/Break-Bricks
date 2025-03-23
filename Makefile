# Compiler & Flags
CC=gcc
CFLAGS=
LIBS=-lraylib -lm -lpthread -lopengl32 -lgdi32 -lwinmm -static

# Daftar File
SRC=src/main.c src/paddle.c src/BOLA.c src/block.c src/stopwatch.c src/nyawa.c src/skor.c src/leaderboard.c src/level.c src/mainmenu.c src/sound.c src/layout.c src/background.c
OBJ=$(SRC:.c=.o)

# Nama Output
TARGET=BreakBricks

# Rule Utama
all: $(TARGET)

# Cara Kompilasi
$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LIBS)

# Kompilasi File .c menjadi .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Bersihkan File yang Tidak Perlu
clean:
	rm -f src/*.o $(TARGET)
