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


    // load scarfy
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;


    // is rectangle in air?
    bool isInAir{};
    // jump velocity(pixels per sec)
    const int jumpVelocity{-600};

    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // dekltatime (time since last frame)
        const float dT{GetFrameTime()};

        // start drawning
        BeginDrawing();
        ClearBackground(BLUE);

        // perform ground check
        if (scarfyPos.y >= windowHeight - scarfyRec.height)
        {
            // rectangle is on ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // rectangle in sky
            velocity += gravity * dT;
            isInAir = true;
        }

        // jump
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVelocity;
        }
        
        // update position
        scarfyPos.y += velocity * dT;

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // stop drawning
        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}