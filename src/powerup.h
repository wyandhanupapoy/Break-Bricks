#ifndef POWERUP_H
#define POWERUP_H

#include <raylib.h>

// Forward declarations
// Ensure these match the actual struct names if they are typedef'd elsewhere
// For PaddleNode and PaddleList, the structs are defined in paddle.h
// For BolaList, it's defined in BOLA.h
struct PaddleNode;
struct PaddleList;
struct BolaList;

typedef enum {
    POWERUP_TRIPLE_BALL,
    POWERUP_LONG_PADDLE
} PowerUpType;

typedef struct PowerUpNode {
    Rectangle rect;
    PowerUpType type;
    bool active;
    float duration; // Duration the power-up effect lasts when collected
    struct PowerUpNode *next;
} PowerUpNode;

typedef struct PowerUpList {
    PowerUpNode *head; // List of falling power-up items
} PowerUpList;

// Functions
void InitPowerUp(PowerUpList *list);
void AddPowerUp(PowerUpList *list, PowerUpType type, Vector2 position);

// UpdatePowerUp now takes PaddleList to check collision with any active paddle
void UpdatePowerUp(PowerUpList *fallingPowerUpList, struct PaddleList *paddleList, struct BolaList *bolaList, float deltaTime);

void DrawPowerUp(PowerUpList *list);
void FreePowerUp(PowerUpList *list); // Frees the list of falling power-ups

// ActivatePowerUp applies an effect to a specific paddle
void ActivatePowerUp(PowerUpType type, struct PaddleNode *paddle_node, struct BolaList *bolaList, float duration);

// UpdateActivePowerUps updates effects already active on a specific paddle
void UpdateActivePowerUps(struct PaddleNode *paddle_node, float deltaTime);

#endif // POWERUP_H