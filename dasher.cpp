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
        }
        else
        {
            // rectangle in sky
            velocity += gravity;
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            velocity -= 10;
        }
        
        // update position
        posY += velocity;

        DrawRectangle(windowWidth/2, posY, width, height, WHITE);

        // stop drawning
        EndDrawing();
    }
    CloseWindow();
}