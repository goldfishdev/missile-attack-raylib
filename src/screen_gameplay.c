


#include "raylib.h"
#include "screens.h"
#include <stdio.h>
//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
Rectangle player = {100, 100, 40, 40 };
float playerSpeed = 4.3f;
//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    Rectangle player = {100, 100, 40, 40 };
    

}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!

    if (IsKeyDown(KEY_W)) {
        player.y -= playerSpeed;
    }
    if (IsKeyDown(KEY_S)) {
        player.y += playerSpeed;
    }
    if (IsKeyDown(KEY_A) && player.x > 0){
        player.x -= playerSpeed;
        if (playerTexture.width > 0) {
            playerTexture.width = -playerTexture.width;
        }
        
    }
    if (IsKeyDown(KEY_D) && player.x < 640 - player.width) {
        player.x += playerSpeed;
    }

}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // TODO: Draw GAMEPLAY screen here!
    Vector2 pos = { 20, 10 };
    DrawTextEx(font, "GAMEPLAY SCREEN", pos, font.baseSize*3.0f, 4, WHITE);
    //DrawRectangleRec(player, RED);
    DrawTextureEx(playerTexture, (Vector2) {player.x, player.y}, 0.0f, 0.4f, WHITE);
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