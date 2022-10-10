#include "raylib.h"
int main()
{
    // window dimensions
    const int windowWidth{512};
    const int windowHeight{380};

    // initialize window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    SetTargetFPS(60);
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(BLUE);

        EndDrawing();
    }
}