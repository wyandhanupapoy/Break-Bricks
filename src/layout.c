// Nama Pembuat: Nezya Zulfa Fauziah  
// Nama Fitur: Layout  
// Deskripsi: Fitur layout mengatur tampilan elemen-elemen dalam game **Break Bricks** agar lebih rapi dan intuitif. 
// Arena permainan menampilkan paddle, bola, dan blok, sementara panel di sisi kanan menampilkan skor, nyawa, dan stopwatch. 
// Instruksi kontrol juga ditampilkan untuk memudahkan pemain. Dengan tata letak yang terorganisir, permainan menjadi lebih nyaman dan interaktif.

#include "layout.h"
#include "raylib.h"
#include <stdio.h>

// Fungsi untuk menampilkan layar pause
void DrawPauseScreen()
{
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.5f)); 
    DrawText("PAUSED", 400, 300, 40, WHITE);  
    DrawText("Press P to resume", 390, 350, 20, WHITE); 
}

// Fungsi untuk menampilkan informasi tim pengembang
void DrawInfo()
{
    DrawText("Ahmad Habib Mutaqqin (241511065)", SCREEN_WIDTH / 2 - 160, 250, 20, WHITE);
    DrawText("Muhammad Brata Hadinata (241511082)", SCREEN_WIDTH / 2 - 160, 300, 20, WHITE);
    DrawText("Muhammad Raihan Abubakar (241511084)", SCREEN_WIDTH / 2 - 160, 350, 20, WHITE);
    DrawText("Nezya Zulfa Fauziah (241511085)", SCREEN_WIDTH / 2 - 160, 400, 20, WHITE);
    DrawText("Siti Soviyyah (241511090)", SCREEN_WIDTH / 2 - 160, 450, 20, WHITE);
    DrawText("Wyandhanu Maulidan Nugraha (241511092)", SCREEN_WIDTH / 2 - 160, 500, 20, WHITE);
}

// Fungsi untuk menampilkan layar Game Over
void DrawGameOverScreen()
{
    ClearBackground(RAYWHITE); 
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE); 
    DrawText("GAME OVER", 370, 300, 40, RED); 
    DrawText("Returning to menu...", 400, 350, 20, DARKGRAY); 
}
// Fungsi untuk menampilkan layar kemenangan
void DrawWinScreen()
{
    ClearBackground(RAYWHITE); 
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
    DrawText("YOU WIN!", 370, 300, 40, GREEN); 
    DrawText("Returning to menu...", 370, 350, 20, DARKGRAY); 
}

// Fungsi untuk menampilkan informasi kontrol permainan di bagian bawah layar
void DrawControlInfo()
{
    DrawRectangle(0, 620, 830, 30, LIGHTGRAY); 
    DrawText("<- -> Move   |   P - Pause   |   F - Fullscreen   |   Esc - Exit   |   M - Mute", 15, 625, 20, BLACK);
}