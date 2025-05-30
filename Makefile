# Nama Compiler
CC = gcc

# Nama Target Executable (di root proyek)
TARGET_NAME = BreakBricks
TARGET = $(TARGET_NAME).exe

# Direktori Source
SRC_DIR = src

# Placeholder untuk path Raylib (SESUAIKAN JIKA PERLU)
# Jika perintah gcc Anda sudah berjalan tanpa -I dan -L spesifik untuk Raylib,
# kemungkinan path ini sudah dikenali oleh MinGW Anda.
# Contoh untuk MinGW64 jika diinstal via MSYS2:
# RAYLIB_INCLUDE_PATH = /mingw64/include
# RAYLIB_LIB_PATH = /mingw64/lib
# Jika Anda mengunduh Raylib manual, pathnya akan berbeda, misal: C:/raylib/raylib/src
RAYLIB_INCLUDE_PATH = # Biarkan kosong jika GCC sudah menemukannya, atau isi pathnya
RAYLIB_LIB_PATH =   # Biarkan kosong jika GCC sudah menemukannya, atau isi pathnya

# Flags untuk Compiler
# -I$(SRC_DIR): Untuk header lokal Anda di folder src
# -Wall -g : Warning dan debug symbols
# -O2 : Optimasi
CFLAGS = -Wall -g -O2 -I$(SRC_DIR)
# Tambahkan path include Raylib jika RAYLIB_INCLUDE_PATH diisi
ifneq ($(RAYLIB_INCLUDE_PATH),)
CFLAGS += -I$(RAYLIB_INCLUDE_PATH)
endif

# Flags untuk Linker (path library)
LDFLAGS =
# Tambahkan path lib Raylib jika RAYLIB_LIB_PATH diisi
ifneq ($(RAYLIB_LIB_PATH),)
LDFLAGS += -L$(RAYLIB_LIB_PATH)
endif

# Libraries yang akan di-link
# -lopengl32 sering dibutuhkan oleh Raylib di Windows selain yang Anda sebutkan.
# -lm untuk fungsi matematika dari math.h yang Anda gunakan.
LIBS = -lraylib -lwinmm -lgdi32 -lopengl32 -lm

# Mencari semua file .c di direktori src
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# Target default: build semua
all: $(TARGET)

# Aturan untuk membuat executable target
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LIBS)
	@echo "Build Selesai: $(TARGET)"

# Target untuk membersihkan file hasil build
clean:
	@echo "Membersihkan file build..."
	rm -f $(TARGET)
	# Hapus leaderboard.dat dari src jika ada (sebaiknya dipindahkan)
	rm -f $(SRC_DIR)/leaderboard.dat
	# Hapus nyawa.exe dari src jika ada
	rm -f $(SRC_DIR)/nyawa.exe
	@echo "Selesai."

# Target untuk menjalankan game
run: $(TARGET)
	@echo "Menjalankan $(TARGET)..."
	./$(TARGET)

# Menandai target yang bukan nama file
.PHONY: all clean run