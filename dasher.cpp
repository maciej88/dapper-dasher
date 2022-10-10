#include "raylib.h"
int main()
{
    // window dimensions
    const int windowWidth{512};
    const int windowHeight{380};

    // initialize window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    // rectangle dimensions
    const int width{50};
    const int height{80};

    int posY{windowHeight - height};
    int velocity{-10};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // start drawning
        BeginDrawing();
        ClearBackground(BLUE);

        posY += velocity;

        DrawRectangle(windowWidth/2, posY, width, height, WHITE);

        // stop drawning
        EndDrawing();
    }
    CloseWindow();
}