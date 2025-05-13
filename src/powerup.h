#ifndef POWERUP_H
#define POWERUP_H

#include <raylib.h>
#include <stdbool.h>
#include "paddle.h"
#include "BOLA.h"
#include "nyawa.h"

// Define power-up types
typedef enum {
    POWERUP_WIDER_PADDLE,   // Memperlebar paddle
    POWERUP_SLOW_BALL,      // Memperlambat bola
    POWERUP_MULTI_BALL,     // Menambah bola baru
    POWERUP_EXTRA_LIFE,     // Menambah nyawa
    POWERUP_STRONGER_BALL,  // Bola jadi lebih kuat (menghancurkan block dengan sekali pukul)
    POWERUP_COUNT           // Jumlah total jenis power-up
} PowerUpType;

// Define power-up structure
typedef struct PowerUp {
    Rectangle rect;         // Bentuk dan posisi power-up
    Color color;            // Warna power-up
    bool active;            // Status aktif power-up
    float speed;            // Kecepatan jatuh
    PowerUpType type;       // Jenis power-up
    float duration;         // Durasi efek power-up (dalam detik)
    float timer;            // Timer untuk efek power-up
    bool isEffectActive;    // Status efek power-up aktif
    struct PowerUp* next;   // Pointer ke power-up berikutnya untuk linked list
} PowerUp;

// Function prototypes
void InitPowerUpSystem(void);
void SpawnPowerUp(float x, float y);
void UpdatePowerUps(PowerUp** powerUpList, Paddle paddles[PADDLE_ROWS][PADDLE_COLS], 
                   Bola bola[BOLA_ROWS][BOLA_COLS], Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM]);
void DrawPowerUps(PowerUp* powerUpList);
void CleanupPowerUps(PowerUp** powerUpList);
void ApplyPowerUpEffect(PowerUpType type, Paddle paddles[PADDLE_ROWS][PADDLE_COLS], 
                       Bola bola[BOLA_ROWS][BOLA_COLS], Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM], PowerUp* powerUp);
void UpdatePowerUpEffects(PowerUp* powerUpList, Paddle paddles[PADDLE_ROWS][PADDLE_COLS], Bola bola[BOLA_ROWS][BOLA_COLS]);
void RevertPowerUpEffect(PowerUpType type, Paddle paddles[PADDLE_ROWS][PADDLE_COLS], Bola bola[BOLA_ROWS][BOLA_COLS]);

// Added function to get the pointer to the global powerUpList
PowerUp** GetPowerUpListPtr(void);

#endif // POWERUP_H