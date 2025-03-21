# Nama file output
TARGET = my_program.exe

# Direktori sumber dan objek
SRCDIR = .
OBJDIR = ./obj
SOURCES = $(SRCDIR)/main.c $(SRCDIR)/BOLA.c $(SRCDIR)/mainmenu.c $(SRCDIR)/level.c $(SRCDIR)/block.c $(SRCDIR)/layout.c $(SRCDIR)/nyawa.c $(SRCDIR)/paddle.c $(SRCDIR)/skor.c $(SRCDIR)/sound.c $(SRCDIR)/stopwatch.c
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Pengaturan Compiler dan Linker
CC = gcc
CFLAGS = -Wall -I/mingw64/include -std=c99
LDFLAGS = -L/mingw64/lib -lraylib -lopengl32 -lm -lwinuser

# Membuat folder obj jika belum ada
$(shell mkdir -p $(OBJDIR))

# Aturan default (compile dan link)
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Aturan untuk mengompilasi file .c menjadi file .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Membersihkan file objek dan file output
clean:
	rm -rf $(OBJDIR) $(TARGET)
