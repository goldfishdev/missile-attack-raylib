#include "raylib.h"
#include "screens.h"
#include <stdio.h>
#include <math.h>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
float playerSpeed = 300.0f;                  // Player speed, should match the Godot version
Rectangle player = {100, 100, 37, 37};       // Player rect
Rectangle playerSourceRect = {0, 0, 63, 63}; // Source rect for player sprite
Rectangle bombSourceRect = {0, 0, 26, 26};   // Source rect for bomb sprite (scaled)
bool canShoot = true;

Bomb bombs[100000];                          // Maximum bombs (adjustable if needed)
int bombCount = 0;                           // Track the number of active bombs
const float bombBaseSpeed = 60.0f;           // Default speed of bombs when dropped
Timer shootTimer;

float currentTime;
float endTime;
float remainingTime;
//----------------------------------------------------------------------------------
// Function Declarations
//----------------------------------------------------------------------------------
void DropBomb(Vector2 pos);
void UpdateBombs();
void StartTimer(Timer *timer, double lifetime);

bool TimerDone(Timer timer);
//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization
void InitGameplayScreen(void)
{
    framesCounter = 0; // Reset the frame counter
    shootTimer.lifeTime = 1;
    shootTimer.startTime = GetTime();
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // Player movement
    if (IsKeyDown(KEY_W) && player.y > -5) {
        player.y -= playerSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_S)) {
        player.y += playerSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_A) && player.x > 0) {
        player.x -= playerSpeed * GetFrameTime();
        if (playerSourceRect.width > 0) {  // Flip sprite on moving left
            playerSourceRect.width *= -1;
        }
    }
    if (IsKeyDown(KEY_D) && player.x < 640 - player.width) {
        player.x += playerSpeed * GetFrameTime();
        if (playerSourceRect.width < 0) { // Flip sprite on moving right
            playerSourceRect.width *= -1;
        }
    }

    // Drop bomb when spacebar is pressed
    if (IsKeyDown(KEY_SPACE) && canShoot) {
        DropBomb((Vector2){ player.x, player.y }); // Drop at player's position
        canShoot = false;
        // add timer here
        Timer *tmr = &shootTimer;
        StartTimer(tmr, 0.5);
    }
    if (TimerDone(shootTimer) && !canShoot) {
        printf("DONEOENEONEONE");
        canShoot = true;
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // Draw player
    DrawTexturePro(playerTexture, playerSourceRect, player, (Vector2){0, 0}, 0, WHITE);
    
    // Update and draw bombs
    UpdateBombs();
    for (int i = 0; i < bombCount; i++) {
        if (bombs[i].active) {
            DrawTexture(bombTexture, bombs[i].position.x, bombs[i].position.y, WHITE);
        }
    }
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // Unload textures when done
    UnloadTexture(playerTexture);
    UnloadTexture(bombTexture);
}

// Check if gameplay screen should finish
int FinishGameplayScreen(void)
{
    return finishScreen;
}

void DropBomb(Vector2 pos)
{
    if (bombCount < 100000) {
        bombs[bombCount].position = (Vector2){ player.x + player.width / 4, player.y + player.height / 1.5 };
        bombs[bombCount].speed = bombBaseSpeed;
        bombs[bombCount].active = true;
        bombCount++;
    }
}

// Update bomb position and speed
void UpdateBombs()
{
    for (int i = 0; i < bombCount; i++) {
        if (bombs[i].active) {
            bombs[i].position.y += bombs[i].speed * GetFrameTime();
            bombs[i].speed += 10;
            
        }

        if (bombs[i].position.y > 600) {
            bombs[i].active = false;
        }
    }
}

void StartTimer(Timer *timer, double lifetime)
{
    timer->startTime = GetTime();
    timer->lifeTime = lifetime;
}

bool TimerDone(Timer timer)
{
    return GetTime() - timer.startTime >= timer.lifeTime;
}

double GetElapsed(Timer timer)
{
    return GetTime() - timer.startTime;
}