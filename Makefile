# Nama Compiler
CC = gcc

# Nama Target Executable
TARGET_NAME = BreakBricks
# Ekstensi untuk executable (.exe untuk Windows)
EXT = .exe

# Direktori
SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/$(TARGET_NAME)$(EXT)

# Flags untuk Compiler
# -Wall: Menampilkan semua warning
# -g: Menyertakan debug symbols (berguna untuk debugging dengan GDB)
# -I$(SRC_DIR): Menambahkan direktori src ke include path
# -O2: Optimasi level 2 (bisa diubah atau dihapus saat debugging)
#
# 🚩 PENTING: Ganti /path/to/raylib-mingw/include dengan path ke direktori include Raylib Anda
# Contoh: C:/raylib/raylib/src (jika dari source) atau C:/msys64/mingw64/include (jika via pacman)
RAYLIB_INCLUDE_PATH = /path/to/raylib-mingw/include
CFLAGS = -Wall -g -O2 -I$(SRC_DIR) -I$(RAYLIB_INCLUDE_PATH)

# Flags untuk Linker
# 🚩 PENTING: Ganti /path/to/raylib-mingw/lib dengan path ke direktori lib Raylib Anda
# Contoh: C:/raylib/raylib/src (jika build dari source dan static) atau C:/msys64/mingw64/lib (jika via pacman)
RAYLIB_LIB_PATH = /path/to/raylib-mingw/lib
LDFLAGS = -L$(RAYLIB_LIB_PATH)

# Libraries yang akan di-link
# Untuk Raylib di MinGW, biasanya: -lraylib -lopengl32 -lgdi32 -lwinmm
# -lm untuk library matematika (digunakan di beberapa file Anda)
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm -lm

# Ekspor path agar Raylib (jika dinamis) bisa ditemukan saat runtime di Windows
# Hanya relevan jika Raylib DLL tidak ada di PATH sistem atau direktori executable
# export PATH := $(RAYLIB_LIB_PATH):$(PATH)

# Mencari semua file .c di direktori src
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# Membuat daftar file object (.o) di direktori build, sesuai dengan file .c di src
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

# Target default: build semua
all: $(TARGET)

# Aturan untuk membuat executable target
$(TARGET): $(OBJECTS)
	@mkdir -p $(@D) # Membuat direktori build jika belum ada (@D adalah direktori dari target)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)
	@echo "Build Selesai: $(TARGET)"

# Aturan pola untuk membuat file object (.o) dari file source (.c)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D) # Membuat direktori build jika belum ada
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled: $< -> $@"

# Target untuk membersihkan file hasil build
clean:
	@echo "Membersihkan file build..."
	rm -f $(TARGET)
	rm -f $(BUILD_DIR)/*.o
	# Hapus leaderboard.dat dari src jika ada (sebaiknya dipindahkan)
	rm -f $(SRC_DIR)/leaderboard.dat
	# Hapus nyawa.exe dari src jika ada (sebaiknya tidak ada executable di src)
	rm -f $(SRC_DIR)/nyawa.exe
	@echo "Selesai."

# Menandai target yang bukan nama file
.PHONY: all clean

# Target untuk menjalankan game dari direktori build
run: all
	@echo "Menjalankan game..."
	cd $(BUILD_DIR) && ./$(TARGET_NAME)$(EXT)
	# Alternatif jika aset ada di root proyek:
	# ./$(TARGET)