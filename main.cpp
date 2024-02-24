#include <raylib.h>
#include <iostream>
#include "game.h"
#include "colors.h"

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{

    // Initaialize Window
    InitWindow(500, 620, "raylib-tetris");

    // Setting FPS
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    Game game = Game();

    while (!WindowShouldClose())
    {
        game.HandleInput();
        UpdateMusicStream(game.music);

        if (EventTriggered(0.15))
        {
            game.MoveBlockDown();
        }

        // Begin Drawing
        BeginDrawing();

        // Clear or refresh Background
        ClearBackground(darkBlue);

        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);          // score title
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue); // score box

        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE); // score text
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);                            // next block
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
        if (game.gameOver)
        {
            DrawTextEx(font, "GAME OVER!", {320, 450}, 38, 2, WHITE);
        }
        game.Draw();

        // End Drawing
        EndDrawing();
    }

    // Close window
    CloseWindow();
    return 0;
}