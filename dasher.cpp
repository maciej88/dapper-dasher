#include "raylib.h"
int main()
{
    // window dimensions
    const int windowWidth{512};
    const int windowHeight{380};

    // initialize window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    // acceleration for gravity (px/frame)/frame
    const int gravity{1};

    // rectangle dimensions
    const int width{50};
    const int height{80};

    // is rectangle in air?
    bool isInAir{};
    // jump velocity
    const int jumpVelocity{-22};

    int posY{windowHeight - height};
    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // start drawning
        BeginDrawing();
        ClearBackground(BLUE);

        // perform ground check
        if (posY >= windowHeight - height)
        {
            // rectangle is on ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // rectangle in sky
            velocity += gravity;
            isInAir = true;
        }

        // jump
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVelocity;
        }
        
        // update position
        posY += velocity;

        DrawRectangle(windowWidth/2, posY, width, height, WHITE);

        // stop drawning
        EndDrawing();
    }
    CloseWindow();
}