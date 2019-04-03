#include "Engine.h"

Engine::Engine()
{
    // Get the screen resolution
    // and create an SFML window and view
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    m_Window.create(VideoMode(resolution.x, resolution.y),
            "Timber", Style::Fullscreen);
    
    // Initialize the fullscreen view
    m_MainView.setSize(resolution);
    m_HUDView.reset(FloatRect(0, 0, resolution.x, resolution.y));

    m_BackgroundTexture = TextureHolder::GetTexture("../graphics/background.png");

    // Associate the sprite with the texture
    m_BackgroundSprite.setTexture(m_BackgroundTexture);
} // End Engine constructor

void Engine::run()
{
    // Timing
    Clock clock;

    while (m_Window.isOpen())
    {
        Time dt = clock.restart();
        // Make a decimal fraction from the delta time
        float dtAsSeconds = dt.asSeconds();
        // Call each part of the game loop in run
        input();
        update(dtAsSeconds);
        draw();
    }
}