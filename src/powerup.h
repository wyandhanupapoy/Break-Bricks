#ifndef POWERUP_H
#define POWERUP_H

#include <raylib.h>  // Untuk Rectangle, Texture2D, dll

// Forward declarations
typedef struct Paddle Paddle;
typedef struct BolaList BolaList;
typedef struct PowerUpList PowerUpList;

typedef enum {
    POWERUP_TRIPLE_BALL,
    POWERUP_LONG_PADDLE
} PowerUpType;

typedef struct PowerUpNode {
    Rectangle rect;
    PowerUpType type;
    bool active;
    float duration;
    struct PowerUpNode *next;
} PowerUpNode;

typedef struct PowerUpList {
    PowerUpNode *head;
} PowerUpList;

// Fungsi
void InitPowerUp(PowerUpList *list);
void AddPowerUp(PowerUpList *list, PowerUpType type, Vector2 position);
void UpdatePowerUp(PowerUpList *list, Paddle *paddle, BolaList *bolaList, float deltaTime);
void DrawPowerUp(PowerUpList *list);
void FreePowerUp(PowerUpList *list);
void ActivatePowerUp(PowerUpType type, Paddle *paddle, BolaList *bolaList, float duration);
void UpdateActivePowerUps(Paddle *paddle, float deltaTime);

#endif

