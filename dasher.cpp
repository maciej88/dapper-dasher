#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    // window dimensions
    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;

    // initialize window
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

    // acceleration for gravity (px/frame)/frame
    const int gravity{1'000};

    // load nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // AnimData for nebula
    AnimData nebData
    { 
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // rectangle res
        {windowDimensions[0], windowDimensions[1] - nebula.height/8}, // vector2 pos
        0, // int frame
        1.0/12.0, // float updateTime
        0 // float runTime
    };

    AnimData neb2Data
    {
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // rectangle res
        {windowDimensions[0] + 300, windowDimensions[1] - nebula.height/8}, // vector2 pos
        0, // int frame
        1.0/16, // float updateTime
        0.0 // float runTime
    };

    const int sizeOfNebulae{3};
    AnimData nebulae[sizeOfNebulae]{};

    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 0.0;
    }

    nebulae[0].pos.x = windowDimensions[0];
    nebulae[1].pos.x = windowDimensions[0] + 300;
    nebulae[2].pos.x = windowDimensions[0] + 600;


    // nebula X velocity
    int nebVel{-200};

    // load scarfy
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;


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
        if (scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height)
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
        nebulae[0].pos.x = nebVel * dT;

        // upadate second nebula position
        nebulae[1].pos.x = nebVel * dT;
        
        // update scarfy position
        scarfyData.pos.y += velocity * dT;

        // update scarfie animation frame
        if (!isInAir)
        {
            // update running time
            scarfyData.runningTime += dT;
            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0.0;
                // update animation frame
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
                if (scarfyData.frame > 5)
                {
                     scarfyData.frame = 0;
                }
            }
        }

        // update nebula animation frame
        nebulae[0].runningTime += dT;
        if (nebulae[0].runningTime >= nebulae[0].updateTime)
        {
            nebulae[0].runningTime = 0.0;
            nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
            nebulae[0].frame++;
            if(nebulae[0].frame > 7)
            {
                nebulae[0].frame = 0;
            }
        }
        
        for (int i = 0; i < 3; i++ );
        
        // update nebula 2 animation frame
        nebulae[1].runningTime += dT;
        if (nebulae[1].runningTime >= nebulae[1].updateTime)
        {
            nebulae[1].runningTime = 0.0;
            nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
            nebulae[1].frame++;
            if(nebulae[1].frame > 7)
            {
                nebulae[1].frame = 0;
            }
        }

        // draw nebula
        DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);

        // second nebula
        DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED);

        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // stop drawning
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}