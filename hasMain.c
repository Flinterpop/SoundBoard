/*******************************************************************************************
*
*   raylib [audio] example - Playing sound multiple times
*
*   Example originally created with raylib 4.6
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023 Jeffery Myers (@JeffM2501)
*
********************************************************************************************/

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION

#include "raygui.h"

#define MAX_SOUNDS 10
Sound soundArray[MAX_SOUNDS] = { 0 };
int currentSound;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 520;
    const int screenHeight = 520;

    InitWindow(screenWidth, screenHeight, "raylib [audio] example - playing sound multiple times");

    InitAudioDevice();      // Initialize audio device

    // load the sound list
    soundArray[0] = LoadSound("resources/musicdance.wav");         // Load WAV audio file into the first slot as the 'source' sound
    soundArray[1] = LoadSound("resources/coin.wav");         // Load WAV audio file into the first slot as the 'source' sound
    soundArray[2] = LoadSound("resources/spring.wav");         // Load WAV audio file into the first slot as the 'source' sound
    soundArray[3] = LoadSound("resources/weird.wav");         // Load WAV audio file into the first slot as the 'source' sound
    soundArray[4] = LoadSound("resources/boom.wav");         // Load WAV audio file into the first slot as the 'source' sound
    soundArray[5] = LoadSound("resources/explosion.wav");         // Load WAV audio file into the first slot as the 'source' sound
    soundArray[6] = LoadSound("resources/laser.wav");         // Load WAV audio file into the first slot as the 'source' sound
    soundArray[7] = LoadSound("resources/fanfare2.wav");         // Load WAV audio file into the first slot as the 'source' sound
    soundArray[8] = LoadSound("resources/cheering.wav");         // Load WAV audio file into the first slot as the 'source' sound
    soundArray[9] = LoadSound("resources/boing2.wav");         // Load WAV audio file into the first slot as the 'source' sound

    
    // this sound owns the sample data
    for (int i = 1; i < MAX_SOUNDS; i++)
    {
        soundArray[i] = LoadSoundAlias(soundArray[i]);        // Load an alias of the sound into slots 1-9. These do not own the sound data, but can be played
    }
    currentSound = 0;                                         // set the sound list to the start

    bool showMessageBox = false;



    Font customFont = LoadFontEx("resources/16020_FUTURAM.ttf", 64, NULL, 0);
    GuiSetFont(customFont);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);





    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
    
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_ONE))
        {
            PlaySound(soundArray[0]);            // play the next open sound slotwertasdf
        }


        if (IsKeyPressed(KEY_TWO))
        {
            PlaySound(soundArray[1]);            // play the next open sound slot
        }
        if (IsKeyPressed(KEY_THREE))
        {
            PlaySound(soundArray[2]);            // play the next open sound slot
        }
        if (IsKeyPressed(KEY_FOUR))
        {
            PlaySound(soundArray[3]);            // play the next open sound slot
        }

        if (IsKeyPressed(KEY_FIVE))
        {
            PlaySound(soundArray[4]);            // play the next open sound slot
        }
        if (IsKeyPressed(KEY_SIX))
        {
            PlaySound(soundArray[5]);            // play the next open sound slot
        }
        if (IsKeyPressed(KEY_SEVEN))
        {
            PlaySound(soundArray[6]);            // play the next open sound slot
        }
        if (IsKeyPressed(KEY_EIGHT))
        {
            PlaySound(soundArray[7]);            // play the next open sound slot
        }
        if (IsKeyPressed(KEY_NINE))
        {
            PlaySound(soundArray[8]);            // play the next open sound slot
        }
        if (IsKeyPressed(KEY_ZERO))
        {
            PlaySound(soundArray[9]);            // play the next open sound slot
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            if (GuiButton((Rectangle) { 10, 10, 100, 100 }, "Music"))
            {
                if (IsSoundPlaying(soundArray[0])) StopSound(soundArray[0]);
                else PlaySound(soundArray[0]);
            }

            
            if (GuiButton((Rectangle) { 10, 10 + 100, 100, 100 }, "coin"))
            {
                if (IsSoundPlaying(soundArray[1])) StopSound(soundArray[1]);
                else PlaySound(soundArray[1]);
            }


            if (GuiButton((Rectangle) { 10, 10 + 200, 100, 100 }, "spring"))
            {
                if (IsSoundPlaying(soundArray[2])) StopSound(soundArray[2]);
                else PlaySound(soundArray[2]);
            }

            if (GuiButton((Rectangle) { 10, 10 + 300, 100, 100 }, "weird"))
            {
                if (IsSoundPlaying(soundArray[3])) StopSound(soundArray[3]);
                else PlaySound(soundArray[3]);
            }

            if (GuiButton((Rectangle) { 10, 10 + 400, 100, 100 }, "boom"))
            {
                if (IsSoundPlaying(soundArray[4])) StopSound(soundArray[4]);
                else PlaySound(soundArray[4]);
            }

            if (GuiButton((Rectangle) { 10+100, 10, 100, 100}, "explosion")) PlaySound(soundArray[5]);
            if (GuiButton((Rectangle) { 10 + 100, 10 + 100, 100, 100 }, "laser")) PlaySound(soundArray[6]);
            if (GuiButton((Rectangle) { 10 + 100, 10 + 200, 100, 100}, "fanfare")) PlaySound(soundArray[7]);
            if (GuiButton((Rectangle) { 10 + 100, 10 + 300, 100, 100}, "cheer")) PlaySound(soundArray[8]);
            if (GuiButton((Rectangle) { 10 + 100, 10 + 400, 100, 100}, "boing")) PlaySound(soundArray[9]);





        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    for (int i = 1; i < MAX_SOUNDS; i++)
        UnloadSoundAlias(soundArray[i]);     // Unload sound aliases
    UnloadSound(soundArray[0]);              // Unload source sound data

    UnloadFont(customFont); // Unload the font

    CloseAudioDevice();     // Close audio device

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}