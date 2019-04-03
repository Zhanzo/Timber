#include "Engine.h"

void Engine::input()
{
    Event event;
    while (m_Window.pollEvent(event)) {
        if (event.type == Event::KeyReleased && !m_Paused) {
            // Listen for key presses again
            acceptInput = true;

            // hide the axe
            spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        m_Window.close();
    }

    // Start the game
    if (Keyboard::isKeyPressed(Keyboard::Return)) {
        m_Paused = false;

        // Reset the time and the score
        m_Score = 0;
        m_TimeRemaining = 6;

        // Make all the branches disappear
        for (int i = 1; i < m_NUM_BRANCHES; i++) {
                m_BranchPositions[i] = side::NONE;
        }

        // Make sure the gravestone is hidden
        spriteRIP.setPosition(675, 2000);

        // Move the player into position
        spritePlayer.setPosition(580, 720);

        acceptInput = true;
    }

    // Wrap the player controls to
    // make sure that we are accepting input
    if (acceptInput) {
        // First handle pressing the right cursor key
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
	        // Make sure the player is on the right
	        playerSide = side::RIGHT;
	        score++;

            // Add to the amount of time remaining
            timeRemaining += (2 / score) + 0.15;

            spriteAxe.setPosition(AXE_POSITION_RIGHT,
                        spriteAxe.getPosition().y);

            spritePlayer.setPosition(1200, 720);

            // update the branches
            updateBranches(score);

            // set the log flying to the left
            spriteLog.setPosition(810, 720);
            logSpeedX = -5000;
            logActive = true;

            acceptInput = false;

            // Play a chop sound
            chop.play();
        }

        // Handle the left cursor key
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            // Make sure the player is on the left
            playerSide = side::LEFT;
            score++;

            // Add to the amount of time remaining
            timeRemaining += (2 / score) + 0.15;

            spriteAxe.setPosition(AXE_POSITION_LEFT,
                        spriteAxe.getPosition().y);

            spritePlayer.setPosition(580, 720);

            // update the branches
            updateBranches(score);

            // set the log flying to the left
            spriteLog.setPosition(810, 720);
            logSpeedX = 5000;
            logActive = true;

            acceptInput = false;

            // Play sound
            chop.play();
        }
    }
}