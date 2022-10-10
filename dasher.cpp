#include "raylib.h"
int main()
{
    // window dimensions
    const int windowWidth{512};
    const int windowHeight{380};

    // initialize window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // start drawning
        BeginDrawing();
        ClearBackground(BLUE);

        // stop drawning
        EndDrawing();
    }
    CloseWindow();
}