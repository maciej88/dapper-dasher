#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    // update running time
    data.runningTime += deltaTime;
    if(data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        // update animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }

    }
    return data;
}

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

    const int sizeOfNebulae{6};
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
        nebulae[i].pos.x = windowDimensions[0] + 1 * 300;
    }

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

    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // dekltatime (time since last frame)
        const float dT{GetFrameTime()};

        // start drawning
        BeginDrawing();
        ClearBackground(WHITE);

        bgX -= 20 * dT;
        if (bgX <= -background.width*2)
        {
            bgX = 0.0;
        }


        // draw the background
        Vector2 bgPos{bgX, 0.0};
        DrawTextureEx(background, bgPos, 0.0, 2.0, WHITE);
        Vector2 bg2Pos{bgX + background.width*2, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);


        // perform ground check
        if (isOnGround(scarfyData, windowDimensions[1]))
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

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // each nebula position update
            nebulae[i].pos.x = nebVel * dT;
        }
        
        // update scarfy position
        scarfyData.pos.y += velocity * dT;

        // update scarfie animation frame
        if (!isInAir)
        {
           scarfyData = updateAnimData(scarfyData, dT, 5);
        }

        for (int i = 0; i < sizeOfNebulae; i++ )
        {
             nebulae[i] = updateAnimData(nebulae[i], dT, 7);
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // draw nebula
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // stop drawning
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    CloseWindow();
}