#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h> // Untuk fungsi kbhit() dan getch()
#include <windows.h> // Untuk fungsi Sleep() dan system()

#define BARIS 25
#define KOLOM 40
#define LEBAR_LAYAR 60
#define AREA_GAME_MULAI 15 // Kolom dimana area game dimulai
#define PADDLE_PANJANG 5
#define JUMLAH_BLOK_BARIS 3
#define JUMLAH_BLOK_KOLOM 8
#define TOTAL_BLOK (JUMLAH_BLOK_BARIS * JUMLAH_BLOK_KOLOM)

// Struktur untuk menyimpan data permainan
typedef struct {
    int skor;
    int level;
    int kecepatan;
    char nama[50];
    int waktu_bermain;
    int nyawa;
    int blok_tersisa;
} DataPermainan;

// Struktur untuk paddle
typedef struct {
    int x;
    int y;
    int panjang;
    char bentuk;
} Paddle;

// Struktur untuk bola
typedef struct {
    int x;
    int y;
    int dx; // Kecepatan horizontal (arah X)
    int dy; // Kecepatan vertikal (arah Y)
    char bentuk;
} Bola;

// Struktur untuk blok
typedef struct {
    int x;
    int y;
    int aktif;
    char bentuk;
    int nilai; // Nilai poin saat blok dihancurkan
} Blok;

// Fungsi untuk mengatur posisi kursor
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Fungsi untuk menyembunyikan kursor
void sembunyikanKursor() {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

// Fungsi untuk menampilkan layar
void tampilkanLayar(char layar[BARIS][LEBAR_LAYAR], DataPermainan data) {
    system("cls"); // Membersihkan layar
    
    // Tampilkan bingkai atas
    printf("+");
    for (int i = 0; i < LEBAR_LAYAR - 2; i++) {
        printf("-");
    }
    printf("+\n");
    
    // Tampilkan isi layar
    for (int i = 0; i < BARIS; i++) {
        printf("|");
        for (int j = 0; j < LEBAR_LAYAR - 2; j++) {
            printf("%c", layar[i][j]);
        }
        printf("|\n");
    }
    
    // Tampilkan bingkai bawah
    printf("+");
    for (int i = 0; i < LEBAR_LAYAR - 2; i++) {
        printf("-");
    }
    printf("+\n");
    
    // Tampilkan informasi permainan di bagian bawah layar
    printf("Nama: %s | Skor: %d | Nyawa: %d | Level: %d\n", 
           data.nama, data.skor, data.nyawa, data.level);
}

// Fungsi untuk menginisialisasi layar
void inisialisasiLayar(char layar[BARIS][LEBAR_LAYAR]) {
    // Kosongkan seluruh layar
    for (int i = 0; i < BARIS; i++) {
        for (int j = 0; j < LEBAR_LAYAR - 2; j++) {
            layar[i][j] = ' ';
        }
    }
    
    // Buat garis pemisah antara sisi kiri (informasi) dan sisi kanan (game)
    for (int i = 0; i < BARIS; i++) {
        layar[i][AREA_GAME_MULAI - 1] = '|';
    }
}

// Fungsi untuk menampilkan informasi di sisi kiri
void tampilkanInfoSisiKiri(char layar[BARIS][LEBAR_LAYAR], DataPermainan data) {
    // Judul
    char judul[] = "BREAKOUT";
    int posJudul = (AREA_GAME_MULAI - strlen(judul)) / 2;
    for (int i = 0; i < strlen(judul); i++) {
        layar[2][posJudul + i] = judul[i];
    }
    
    // Informasi skor
    char skorStr[20];
    sprintf(skorStr, "SKOR: %d", data.skor);
    int posSkor = 2;
    for (int i = 0; i < strlen(skorStr); i++) {
        layar[5][posSkor + i] = skorStr[i];
    }
    
    // Informasi nyawa
    char nyawaStr[20];
    sprintf(nyawaStr, "NYAWA: %d", data.nyawa);
    int posNyawa = 2;
    for (int i = 0; i < strlen(nyawaStr); i++) {
        layar[7][posNyawa + i] = nyawaStr[i];
    }
    
    // Informasi level
    char levelStr[20];
    sprintf(levelStr, "LEVEL: %d", data.level);
    int posLevel = 2;
    for (int i = 0; i < strlen(levelStr); i++) {
        layar[9][posLevel + i] = levelStr[i];
    }
    
    // Informasi blok tersisa
    char blokStr[20];
    sprintf(blokStr, "BLOK: %d", data.blok_tersisa);
    int posBlok = 2;
    for (int i = 0; i < strlen(blokStr); i++) {
        layar[11][posBlok + i] = blokStr[i];
    }
    
    // Instruksi kontrol
    char instruksi1[] = "KONTROL:";
    int posInstruksi1 = 2;
    for (int i = 0; i < strlen(instruksi1); i++) {
        layar[14][posInstruksi1 + i] = instruksi1[i];
    }
    
    char instruksi2[] = "A - Kiri";
    int posInstruksi2 = 2;
    for (int i = 0; i < strlen(instruksi2); i++) {
        layar[15][posInstruksi2 + i] = instruksi2[i];
    }
    
    char instruksi3[] = "D - Kanan";
    int posInstruksi3 = 2;
    for (int i = 0; i < strlen(instruksi3); i++) {
        layar[16][posInstruksi3 + i] = instruksi3[i];
    }
    
    char instruksi4[] = "SPACE - Mulai";
    int posInstruksi4 = 2;
    for (int i = 0; i < strlen(instruksi4); i++) {
        layar[17][posInstruksi4 + i] = instruksi4[i];
    }
    
    char instruksi5[] = "Q - Keluar";
    int posInstruksi5 = 2;
    for (int i = 0; i < strlen(instruksi5); i++) {
        layar[18][posInstruksi5 + i] = instruksi5[i];
    }
}

// Inisialisasi paddle
void inisialisasiPaddle(Paddle *paddle) {
    paddle->x = AREA_GAME_MULAI + (LEBAR_LAYAR - AREA_GAME_MULAI) / 2 - PADDLE_PANJANG / 2;
    paddle->y = BARIS - 3;
    paddle->panjang = PADDLE_PANJANG;
    paddle->bentuk = '=';
}

// Menampilkan paddle di layar
void tampilkanPaddle(char layar[BARIS][LEBAR_LAYAR], Paddle paddle) {
    for (int i = 0; i < paddle.panjang; i++) {
        layar[paddle.y][paddle.x + i] = paddle.bentuk;
    }
}

// Inisialisasi bola
void inisialisasiBola(Bola *bola, Paddle paddle) {
    bola->x = paddle.x + paddle.panjang / 2;
    bola->y = paddle.y - 1;
    bola->dx = 0; // Bola diam sampai dimulai
    bola->dy = 0; // Bola diam sampai dimulai
    bola->bentuk = 'O';
}

// Mulai gerakan bola
void mulaiBola(Bola *bola) {
    // Berikan arah acak ke bola saat mulai
    bola->dx = (rand() % 2 == 0) ? 1 : -1;
    bola->dy = -1; // Bergerak ke atas pertama kali
}

// Menampilkan bola di layar
void tampilkanBola(char layar[BARIS][LEBAR_LAYAR], Bola bola) {
    layar[bola.y][bola.x] = bola.bentuk;
}

// Inisialisasi blok
void inisialisasiBlok(Blok blok[JUMLAH_BLOK_BARIS][JUMLAH_BLOK_KOLOM]) {
    int nilai_baris[JUMLAH_BLOK_BARIS] = {30, 20, 10}; // Nilai blok berdasarkan baris
    char bentuk_baris[JUMLAH_BLOK_BARIS] = {'#', '%', '&'}; // Bentuk blok berdasarkan baris
    
    for (int i = 0; i < JUMLAH_BLOK_BARIS; i++) {
        for (int j = 0; j < JUMLAH_BLOK_KOLOM; j++) {
            blok[i][j].x = AREA_GAME_MULAI + 2 + j * 4; // Spasi 4 karakter antar blok
            blok[i][j].y = 3 + i * 2; // Spasi 2 baris antar baris blok
            blok[i][j].aktif = 1;
            blok[i][j].bentuk = bentuk_baris[i];
            blok[i][j].nilai = nilai_baris[i];
        }
    }
}

// Menampilkan blok di layar
void tampilkanBlok(char layar[BARIS][LEBAR_LAYAR], Blok blok[JUMLAH_BLOK_BARIS][JUMLAH_BLOK_KOLOM]) {
    for (int i = 0; i < JUMLAH_BLOK_BARIS; i++) {
        for (int j = 0; j < JUMLAH_BLOK_KOLOM; j++) {
            if (blok[i][j].aktif) {
                layar[blok[i][j].y][blok[i][j].x] = blok[i][j].bentuk;
                layar[blok[i][j].y][blok[i][j].x + 1] = blok[i][j].bentuk;
                layar[blok[i][j].y][blok[i][j].x + 2] = blok[i][j].bentuk;
            }
        }
    }
}

// Gerakan bola dan deteksi tabrakan
int gerakkanBola(Bola *bola, Paddle paddle, Blok blok[JUMLAH_BLOK_BARIS][JUMLAH_BLOK_KOLOM], DataPermainan *data) {
    if (bola->dx == 0 && bola->dy == 0) {
        // Jika bola belum bergerak, ikuti paddle
        bola->x = paddle.x + paddle.panjang / 2;
        bola->y = paddle.y - 1;
        return 0;
    }
    
    // Perbarui posisi bola
    int nextX = bola->x + bola->dx;
    int nextY = bola->y + bola->dy;
    
    // Cek tabrakan dengan dinding
    if (nextX <= AREA_GAME_MULAI || nextX >= LEBAR_LAYAR - 2) {
        bola->dx = -bola->dx; // Pantulan horizontal
        nextX = bola->x + bola->dx; // Hitung ulang posisi berikutnya
    }
    
    if (nextY <= 0) {
        bola->dy = -bola->dy; // Pantulan atas
        nextY = bola->y + bola->dy; // Hitung ulang posisi berikutnya
    }
    
    // Cek jika bola jatuh ke bawah (melewati paddle)
    if (nextY >= BARIS) {
        // Kehilangan bola, kurangi nyawa
        data->nyawa--;
        if (data->nyawa <= 0) {
            return 1; // Game over
        }
        
        // Reset posisi bola
        inisialisasiBola(bola, paddle);
        return 0;
    }
    
    // Cek tabrakan dengan paddle
    if (nextY == paddle.y && nextX >= paddle.x && nextX < paddle.x + paddle.panjang) {
        bola->dy = -bola->dy; // Pantulan vertikal
        
        // Atur arah horizontal berdasarkan posisi hit pada paddle untuk kontrol arah
        int hitPos = nextX - paddle.x;
        if (hitPos < paddle.panjang / 3) {
            bola->dx = -1; // Hit di sebelah kiri paddle, bola ke kiri
        } else if (hitPos > (2 * paddle.panjang) / 3) {
            bola->dx = 1; // Hit di sebelah kanan paddle, bola ke kanan
        }
        
        nextY = bola->y + bola->dy; // Hitung ulang posisi berikutnya
    }
    
    // Cek tabrakan dengan blok
    for (int i = 0; i < JUMLAH_BLOK_BARIS; i++) {
        for (int j = 0; j < JUMLAH_BLOK_KOLOM; j++) {
            if (blok[i][j].aktif) {
                // Cek apakah bola mengenai blok
                if (nextY == blok[i][j].y && 
                    (nextX >= blok[i][j].x && nextX <= blok[i][j].x + 2)) {
                    // Blok terkena!
                    blok[i][j].aktif = 0;
                    data->skor += blok[i][j].nilai;
                    data->blok_tersisa--;
                    
                    // Pantulan bola
                    bola->dy = -bola->dy;
                    nextY = bola->y + bola->dy;
                    
                    // Cek jika semua blok sudah hancur
                    if (data->blok_tersisa <= 0) {
                        return 2; // Level selesai
                    }
                }
            }
        }
    }
    
    // Perbarui posisi bola
    bola->x = nextX;
    bola->y = nextY;
    
    return 0;
}

// Mulai level baru
void mulaiLevelBaru(DataPermainan *data, Paddle *paddle, Bola *bola, Blok blok[JUMLAH_BLOK_BARIS][JUMLAH_BLOK_KOLOM]) {
    data->level++;
    data->kecepatan = data->kecepatan > 10 ? data->kecepatan - 10 : 10;
    data->blok_tersisa = TOTAL_BLOK;
    
    // Reset posisi paddle dan bola
    inisialisasiPaddle(paddle);
    inisialisasiBola(bola, *paddle);
    
    // Setup blok baru
    inisialisasiBlok(blok);
}

// Tampilkan pesan level selesai
void tampilkanLevelSelesai(int level) {
    system("cls");
    printf("\n\n\n");
    printf("\t\tLEVEL %d SELESAI!\n\n", level);
    printf("\t\tTekan tombol apa saja untuk melanjutkan ke level berikutnya...");
    getch();
}

// Tampilkan pesan game over
void tampilkanGameOver(DataPermainan data) {
    system("cls");
    printf("\n\n\n");
    printf("\t\tGAME OVER\n\n");
    printf("\t\tNama: %s\n", data.nama);
    printf("\t\tSkor Akhir: %d\n", data.skor);
    printf("\t\tLevel Dicapai: %d\n", data.level);
    printf("\t\tWaktu Bermain: %d detik\n\n", data.waktu_bermain);
    printf("\t\tTekan tombol apa saja untuk keluar...");
    getch();
}

// Fungsi utama game
void mainkanGame() {
    char layar[BARIS][LEBAR_LAYAR];
    DataPermainan data = {0, 1, 100, "Player", 0, 3, TOTAL_BLOK};
    Paddle paddle;
    Bola bola;
    Blok blok[JUMLAH_BLOK_BARIS][JUMLAH_BLOK_KOLOM];
    time_t waktuMulai, waktuSekarang;
    char input;
    int gameSelesai = 0;
    int bolaBergerak = 0;
    
    // Inisialisasi
    srand(time(NULL));
    sembunyikanKursor();
    
    // Setup awal permainan
    printf("Masukkan nama Anda: ");
    scanf("%s", data.nama);
    
    inisialisasiLayar(layar);
    inisialisasiPaddle(&paddle);
    inisialisasiBola(&bola, paddle);
    inisialisasiBlok(blok);
    
    waktuMulai = time(NULL);
    
    // Loop utama game
    while (!gameSelesai) {
        // Perbarui waktu
        waktuSekarang = time(NULL);
        data.waktu_bermain = (int)(waktuSekarang - waktuMulai);
        
        // Kosongkan layar untuk diperbarui
        inisialisasiLayar(layar);
        
        // Tampilkan informasi di sisi kiri
        tampilkanInfoSisiKiri(layar, data);
        
        // Tampilkan objek game di sisi kanan
        tampilkanPaddle(layar, paddle);
        tampilkanBola(layar, bola);
        tampilkanBlok(layar, blok);
        
        // Tampilkan layar
        tampilkanLayar(layar, data);
        
        // Cek input pengguna
        if (kbhit()) {
            input = getch();
            
            // Proses input
            switch (input) {
                case 'a': case 'A':
                    if (paddle.x > AREA_GAME_MULAI) {
                        paddle.x--;
                    }
                    break;
                case 'd': case 'D':
                    if (paddle.x + paddle.panjang < LEBAR_LAYAR - 2) {
                        paddle.x++;
                    }
                    break;
                case ' ': // Spasi untuk mulai bola bergerak
                    if (!bolaBergerak) {
                        mulaiBola(&bola);
                        bolaBergerak = 1;
                    }
                    break;
                case 'q': case 'Q':
                    gameSelesai = 1;
                    break;
            }
        }
        
        // Gerakan bola dan deteksi tabrakan
        int hasilGerakan = gerakkanBola(&bola, paddle, blok, &data);
        
        // Cek hasil gerakan bola
        if (hasilGerakan == 1) {
            // Game over
            gameSelesai = 1;
        } else if (hasilGerakan == 2) {
            // Level selesai
            tampilkanLevelSelesai(data.level);
            mulaiLevelBaru(&data, &paddle, &bola, blok);
            bolaBergerak = 0;
        }
        
        // Delay
        Sleep(data.kecepatan);
    }
    
    // Tampilkan pesan akhir permainan
    tampilkanGameOver(data);
}

int main() {
    // Setup konsol
    system("title Breakout Game");
    system("mode con cols=65 lines=30");
    
    // Mulai permainan
    mainkanGame();
    
    return 0;
}