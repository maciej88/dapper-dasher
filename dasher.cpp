#include "raylib.h"
int main()
{
    // window dimensions
    const int windowWidth{512};
    const int windowHeight{380};

    // initialize window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    // acceleration for gravity (px/frame)/frame
    const int gravity{1'000};

    // load nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};


    Vector2 nebPos{windowWidth, windowHeight - nebRec.height};

    // nebula animation variables
    int nebFrame{};
    const float nebUpdateTime{1.0 / 12.0};
    float nebRunningTime{};

    // nebula X velocity
    int nebVel{-60};

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

    // animation frame
    int frame{};

    const float updateTime{ 1.0 / 12.0};
    float runningTime{};

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
        // update nebula position
        nebPos.x = nebVel * dT;
        
        // update scarfy position
        scarfyPos.y += velocity * dT;

        // update scarfie animation frame
        if (!isInAir)
        {
            // update running time
            runningTime += dT;
            if (runningTime >= updateTime)
            {
                runningTime = 0.0;
                // update animation frame
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                if (frame > 5)
                {
                    frame = 0;
                }
            }
        }

        // update nebula animation frame
        nebRunningTime += dT;
        if (nebRunningTime >= nebUpdateTime)
        {
            nebRunningTime = 0.0;
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if(frame > 7)
            {
                nebFrame = 0;
            }
        }
        
        // draw nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);

        // draw scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // stop drawning
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}