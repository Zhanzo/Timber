#pragma once
#include <SFML/Graphics.hpp>
#include "Hud.h"
#include "TextureHolder.h"
#include "Side.h"

using namespace sf;

class Engine
{
private:
    // The texture holder 
    TextureHolder th;

    // Create a SoundManager
    SoundManager m_SM;

    // The HUD
    Hud m_Hud;
    int m_FramesSinceLastHUDUpdate = 0;
    int m_TargetFramesPerHUDUpdate = 500;

    // A regular RenderWindow
    RenderWindow m_Window;

    // The main views
    View m_MainView;
    View m_HUDView;

    // Declare a sprite and a texture for the background
    Sprite m_BackgroundSprite;
    Texture m_BackgroundTexture;

    // Track wether the game is running
    bool m_Paused = true;

    // Track the score
    int m_Score = 0;

    // How much time is left in the current level?
    float m_TimeRemaining = 6.0f;
    float m_GameTimeTotal = 0;

    const static int m_NUM_BRANCHES = 6;
    Sprite m_Branches[m_NUM_BRANCHES];
    side m_BranchPositions[m_NUM_BRANCHES];

    // Private functions for internal use only
    void input();
    void update(float dtAsSeconds);
    void draw();

public:
    // The Engine constructor
    Engine();

    // Run will call all the private functions
    void run();
}