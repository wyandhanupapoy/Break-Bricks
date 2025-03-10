#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

int main() {
    // Inisialisasi SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Gagal menginisialisasi SDL: %s\n", SDL_GetError());
        return 1;
    }
    
    SDL_Window *window = SDL_CreateWindow("Stopwatch Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 200, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Gagal membuat jendela: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Gagal membuat renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    printf("=== Stopwatch Game ===\n");
    printf("Tekan ENTER untuk memulai stopwatch...\n");
    getchar(); // Tunggu input sebelum memulai
    
    Uint32 start_time = SDL_GetTicks(); // Mulai stopwatch
    bool running = true;
    
    printf("Stopwatch berjalan... Tekan ENTER untuk berhenti!\n");
    
    while (running) {
        Uint32 current_time = SDL_GetTicks();
        double elapsed_time = (current_time - start_time) / 1000.0;
        
        // Event handling
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        
        // Cek jika tombol ENTER ditekan
        if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RETURN]) {
            running = false;
        }
        
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        // Render update (misalnya menampilkan waktu di UI, butuh SDL_ttf untuk teks)
        printf("\rWaktu: %.2f detik", elapsed_time);
        fflush(stdout);
        
        SDL_RenderPresent(renderer);
        SDL_Delay(100); // Update setiap 100ms
    }
    
    Uint32 end_time = SDL_GetTicks();
    double elapsed_time = (end_time - start_time) / 1000.0;
    int score = (int)(1000 / elapsed_time);
    
    printf("\n\nWaktu akhir: %.2f detik\n", elapsed_time);
    printf("Skor: %d\n", score);
    printf("\nTekan ENTER untuk keluar...\n");
    getchar();
    
    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
