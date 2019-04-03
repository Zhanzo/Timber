#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Hud
{
private:
    Font m_Font;
    Text m_MessageText;
    Text m_ScoreText;
    Text m_FPSText;
    RectangleShape m_TimeBar;

public:
    Hud();

    Text getMessage();

    Text getScore();
    
    Text getFPS();
}