#include "raylib.h"

#define RAYGUI_IMPLEMENTATION

#include "raygui.h"
#include <vector>
#include <string>

#if defined(WIN32) && !defined(_DEBUG)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

//external declarations
std::vector<std::string> LoadSoundFileList();
bool getFileNameNoExtension(const char* path, char* dest);



int buttonWidth = 150;
int buttonHeight = 95;

const int BG_FONT_SIZE = 25;
//const char* labels[] = { "Music","Coin", "Spring","Weird","Boom" ,"Explosion","Laser", "Fanfare","cheer","boing" };

std::vector<std::string> m_AudioFileList;
std::vector<Sound> m_SoundsList;
int NumSounds = 0;

int getKeyCode(int x)
{
    if (x < 9) return x + 49;
    if (x >= 9) return 65 - 9 + x;
    else return 0;
}

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

    if (playing) GuiDrawRectangle(bounds, GuiGetStyle(BUTTON, BORDER_WIDTH), BLACK, RED);
    else GuiDrawRectangle(bounds, GuiGetStyle(BUTTON, BORDER_WIDTH), BLACK, GREEN);
    
    Rectangle top = bounds;
    top.height = bounds.height / 2;
    Rectangle bottom = bounds;
    bottom.height = top.height;
    bottom.y = top.y + top.height;
    GuiDrawText(text, GetTextBounds(BUTTON, top), GuiGetStyle(BUTTON, TEXT_ALIGNMENT), BLACK);
    
    char buf[20];
    sprintf(buf, "%c", getKeyCode(keyindex));
    GuiDrawText(buf, GetTextBounds(BUTTON, bottom), GuiGetStyle(BUTTON, TEXT_ALIGNMENT), GetColor(GuiGetStyle(BUTTON, TEXT + (state * 3))));


    if (state == STATE_FOCUSED) GuiTooltip(bounds);

    return result;      // Button pressed: result = 1
}


void SoundButton(char * label, int x, int y, int soundIndex)
{
    bool playing = IsSoundPlaying(m_SoundsList[soundIndex]);
    Rectangle r;
    r.x = x;
    r.y = y;
    r.width = buttonWidth;
    r.height = buttonHeight;

    if (bg_GuiButton(r, label,playing, soundIndex))
    {
        if (playing) StopSound(m_SoundsList[soundIndex]);
        else PlaySound(m_SoundsList[soundIndex]);
    }
}


int main(void)
{
    InitAudioDevice();      // Initialize audio device

    m_AudioFileList = LoadSoundFileList();
    for (auto& sn : m_AudioFileList)
    {
        Sound s = LoadSound(sn.c_str());
        m_SoundsList.push_back(s);
    }

    NumSounds = m_SoundsList.size();

    int NumRows = NumSounds / 5;
    if ((NumSounds % 5) > 0) ++NumRows;

    const int screenWidth = 10 + (buttonWidth + 5) * 5;
    const int screenHeight = 10 + (5+ buttonHeight)*  NumRows;

    InitWindow(screenWidth, screenHeight, "Finley's Soundboard");



    Font customFont = LoadFontEx("resources/16020_FUTURAM.ttf", 64, NULL, 0);
    GuiSetFont(customFont);
    GuiSetStyle(DEFAULT, TEXT_SIZE, BG_FONT_SIZE);


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        // Update
        for (int x=0;x< NumSounds;x++)
            if (IsKeyPressed(getKeyCode(x))) 
            {
                if (IsSoundPlaying(m_SoundsList[x])) StopSound(m_SoundsList[x]);
                else PlaySound(m_SoundsList[x]);
            }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            for (int x=0;x< NumSounds;x++)
            {
                int row = x % 5;
                int col = x / 5;
                //SoundButton((char *)labels[x%10], 10 + row *100, 10 + col * 100, x);
                char fname[300];
                getFileNameNoExtension((const char*)m_AudioFileList[x].c_str(), fname);

                SoundButton(fname, 10 + row * (buttonWidth +5), 10 + col * (buttonHeight+5), x);
            }




        EndDrawing();
    }


    for (auto &sn : m_SoundsList)
    {
        UnloadSound(sn);              // Unload source sound data
    }

    UnloadFont(customFont); // Unload the font

    CloseAudioDevice();     // Close audio device

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}