// src/powerup.h
#ifndef POWERUP_H
#define POWERUP_H

#include <raylib.h>

// Forward declarations (ini sudah benar)
struct PaddleNode;
struct PaddleList;
struct BolaList;

#define POWERUP_SPAWN_CHANCE_PERCENT 30
#define POWERUP_DEFAULT_DURATION 10.0f
#define LONG_PADDLE_INCREMENT_VALUE 40.0f // PADDLE_WIDTH akan datang dari paddle.h
                                                   // atau perlu didefinisikan di sini/game_state.h

typedef enum {
    POWERUP_TRIPLE_BALL,
    POWERUP_LONG_PADDLE
} PowerUpType; // Definisi penuh ada di sini

// ... (sisa kode powerup.h tetap sama) ...
typedef struct PowerUpNode {
    Rectangle rect;
    PowerUpType type;
    bool active;
    struct PowerUpNode *next;
} PowerUpNode;

typedef struct PowerUpList {
    PowerUpNode *head;
} PowerUpList;

void InitPowerUp(PowerUpList *list);
void AddPowerUp(PowerUpList *list, PowerUpType type, Vector2 position);
void UpdatePowerUp(PowerUpList *fallingPowerUpList, struct PaddleList *paddleList, struct BolaList *bolaList, float deltaTime);
void DrawPowerUp(PowerUpList *list);
void FreePowerUp(PowerUpList *list);
void ActivatePowerUp(PowerUpType type, struct PaddleNode *paddle_node, struct BolaList *bolaList);
void UpdateActivePowerUps(struct PaddleNode *paddle_node, float deltaTime);

#endif // POWERUP_H