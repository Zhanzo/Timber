#include "Hud.h"

Hud::Hud()
{
    Vector2u resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    // Load the font
    m_Font.loadFromFile("../fonts/KOMIKAP_.ttf");

    // FPS
    m_FPSText.setFont(m_Font);
    m_FPSText.setFillColor(Color::White);
    m_FPSText.setCharacterSize(100);
    m_FPSText.setPosition(resolution.x - 150, 0);

    // Message
    m_MessageText.setFont(m_Font);
    m_MessageText.setString("Press Enter to start!");
    m_MessageText.setFillColor(Color::White);
    m_MessageText.setCharacterSize(75);
    // Position the text
    FloatRect textRect = m_MessageText.getLocalBounds();
    m_MessageText.setOrigin(textRect.left + textRect.width / 2.0f,
                          textRect.top + textRect.height / 2.0f);
    m_MessageText.setPosition(resolution.x / 2.0f, resolution.y / 2.0f);

    // Score
    m_ScoreText.setFont(m_Font);
    m_ScoreText.setString("Score = 0");
    m_ScoreText.setFillColor(Color::White);
    m_ScoreText.setCharacterSize(100);
    m_ScoreText.setPosition(25, 0);

    // Timebar
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    m_TimeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    m_TimeBar.setFillColor(Color::Red);
    m_TimeBar.setPosition((resolution.x / 2) - timeBarStartWidth / 2, resolution.y);
}

Text Hud::getMessage()
{
    return m_MessageText;
}

Text Hud::getScore()
{
    return m_ScoreText;
}

Text Hud::getFPS()
{
    return m_FPSText;
}

