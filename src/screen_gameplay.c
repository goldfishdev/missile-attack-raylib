#include "raylib.h"
#include "screens.h"
#include <stdio.h>
//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
float playerSpeed = 300.0f;
Rectangle player = {100, 100, 37, 37 };
Rectangle source  = (Rectangle){0, 0 , 63, 63}; // The sprite is 64x64, but for some reason, and extra pixel gets displayed when it's flipped. idk.
Bomb bombs[10];
int bombCount = 0;
int bombBaseSpeed = 60;


//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------
// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    framesCounter = 0;
}   

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    if (IsKeyDown(KEY_W)) {
        player.y -= playerSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_S)) {
        player.y += playerSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_A) && player.x > 0){
        player.x -= playerSpeed * GetFrameTime();
        if (source.width > 0) {
            source.width *= -1;
        }
    }
    if (IsKeyDown(KEY_D) && player.x < 640 - player.width) {
        player.x += playerSpeed * GetFrameTime();
        if (source.width < 0) {
            source.width *= -1;
        }
    }

}
// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    Vector2 pos = { 20, 10 };
    //DrawTextEx(font, "GAMEPLAY SCREEN", pos, font.baseSize*3.0f, 4, WHITE);
    DrawTexturePro(playerTexture, source, player, (Vector2){0, 0}, 0, WHITE);
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
    UnloadTexture(playerTexture);
}   


// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}

void DropBomb(Vector2 pos) {
    if (bombCount < 10) {
    bombs[bombCount].position = (Vector2){ player.x, player.y };
    bombs[bombCount].speed = bombBaseSpeed;
    bombs[bombCount].active = true;
    bombCount++;
    }
}

void UpdateBombs() {
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