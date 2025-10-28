#include "raylib.h"

#define RAYGUI_IMPLEMENTATION

#include "raygui.h"
#include <vector>
#include <string>

#if defined(WIN32) && !defined(_DEBUG)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif


#define MAX_SOUNDS 10
Sound soundArray[MAX_SOUNDS] = { 0 };
int currentSound;


int buttonWidth = 95;
int buttonHeight = 95;


const int BG_FONT_SIZE = 25;
const char* labels[] = { "Music","Coin", "Spring","Weird","Boom" ,"Explosion","Laser", "Fanfare","cheer","boing" };

std::vector<std::string> m_AudioFileList;




/*
bool LoadSoundFiles()
{
    if (GetFileAttributes(L"resources") == INVALID_FILE_ATTRIBUTES)
    {
        puts("Audio Directory (\"resources\") doesn't exist");
        return true;
    }

    std::vector<std::string> fList = LoadFileNamesInFolder("wav", ".wav");

    //if (m_AudioFileList.size() > 0) m_AudioFileList.clear();

    return false;
}
*/



// Button control, returns true when clicked
int bg_GuiButton(Rectangle bounds, const char* text, bool playing, int keyindex)
{
    int result = 0;
    GuiState state = guiState;

    if ((state != STATE_DISABLED) && !guiLocked && !guiControlExclusiveMode)
    {
        Vector2 mousePoint = GetMousePosition();

        // Check button state
        if (CheckCollisionPointRec(mousePoint, bounds))
        {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) state = STATE_PRESSED;
            else state = STATE_FOCUSED;

            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) result = 1;
        }
    }

    //GuiDrawRectangle(bounds, GuiGetStyle(BUTTON, BORDER_WIDTH), GetColor(GuiGetStyle(BUTTON, BORDER + (state * 3))), GetColor(GuiGetStyle(BUTTON, BASE + (state * 3))));
    if (playing) GuiDrawRectangle(bounds, GuiGetStyle(BUTTON, BORDER_WIDTH), BLACK, RED);
    else GuiDrawRectangle(bounds, GuiGetStyle(BUTTON, BORDER_WIDTH), BLACK, GREEN);

    
    Rectangle top = bounds;
    top.height = bounds.height / 2;
    Rectangle bottom = bounds;
    bottom.height = top.height;
    bottom.y = top.y + top.height;
    GuiDrawText(text, GetTextBounds(BUTTON, top), GuiGetStyle(BUTTON, TEXT_ALIGNMENT), BLACK);
    
    char buf[20];
    sprintf(buf, "%d", keyindex%10);
    GuiDrawText(buf, GetTextBounds(BUTTON, bottom), GuiGetStyle(BUTTON, TEXT_ALIGNMENT), GetColor(GuiGetStyle(BUTTON, TEXT + (state * 3))));


    if (state == STATE_FOCUSED) GuiTooltip(bounds);

    return result;      // Button pressed: result = 1
}


void SoundButton(char * label, int x, int y, int soundIndex)
{
    bool playing = IsSoundPlaying(soundArray[soundIndex]);

    r.x = x;
    r.y = y;
    r.width = buttonWidth;
    r.height = buttonHeight;

    if (bg_GuiButton(r, label,playing, soundIndex+1))
    {
        if (playing) StopSound(soundArray[soundIndex]);
        else PlaySound(soundArray[soundIndex]);
    }
}


KeyboardKey keyList[10] = {KEY_ONE,KEY_TWO, KEY_THREE,KEY_FOUR,KEY_FIVE, KEY_SIX, KEY_SEVEN, KEY_EIGHT, KEY_NINE, KEY_ZERO};


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 520;
    const int screenHeight = 520;

    InitWindow(screenWidth, screenHeight, "Finley's Soundboard");

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
    GuiSetStyle(DEFAULT, TEXT_SIZE, BG_FONT_SIZE);





    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        // Update
        for (int x=0;x<10;x++)
            if (IsKeyPressed(keyList[x]))
            {
                if (IsSoundPlaying(soundArray[x])) StopSound(soundArray[x]);
                else PlaySound(soundArray[x]);            
            }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            for (int x=0;x< 10;x++)
            {
                int row = x % 5;
                int col = x / 5;
                SoundButton((char *)labels[x], 10 + row *100, 10 + col * 100, x);
            }




        EndDrawing();
    }

    for (int i = 1; i < MAX_SOUNDS; i++)
        UnloadSoundAlias(soundArray[i]);     // Unload sound aliases

    UnloadSound(soundArray[0]);              // Unload source sound data

    UnloadFont(customFont); // Unload the font

    CloseAudioDevice();     // Close audio device

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}