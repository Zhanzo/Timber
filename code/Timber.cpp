// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <sstream>

// Make code easier to type with "using namespace"
using namespace sf;

int main()
{
    // Create a video mode object
    VideoMode vm(1280, 720);
    // Create and open a window for the game (low res)
    RenderWindow window(vm, "Timber!!!");
    View view(sf::FloatRect(0, 0, 1920, 1080));
    window.setView(view);

    // Create a texture to hold a graphic on the GPU
    Texture textureBackground;

    // Load a graphic into the texture
    textureBackground.loadFromFile("../graphics/background.png");

    // Create a sprite
    Sprite spriteBackground;

    // Attach the texture to the sprite
    spriteBackground.setTexture(textureBackground);

    // Set the spriteBackground to cover the screen
    spriteBackground.setPosition(0, 0);

    // Make a tree sprite
    Texture textureTree;
    textureTree.loadFromFile("../graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    // Prepare the bee
    Texture textureBee;
    textureBee.loadFromFile("../graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);

    // Is the bee currently moving?
    bool beeActive = false;

    // How fast can the bee fly?
    float beeSpeed = 0.0f;

    // make 3 cloud sprites from 1 texture
    Texture textureCloud;

    // Load 1 new texture
    textureCloud.loadFromFile("../graphics/cloud.png");

    Sprite spriteClouds[3];
    for (int i = 0; i < 3; i++) {
        // Set the sprite texture
        spriteClouds[i].setTexture(textureCloud);
        // Position the clouds off screen
        spriteClouds[i].setPosition(0, i * 250);
    }

    // Are the clouds currently on screen?
    bool cloudsActive[3];
    for (int i = 0; i < 3; i++) {
        cloudsActive[i] = false;
    }

    // How fast is each cloud?
    float cloudsSpeed[3];
    for (int i = 0; i < 3; i++) {
        cloudsSpeed[i] = 0.0f;
    }

    // Variables to control time itself
    Clock clock;

    // Time bar
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    // Track wether the game is running
    bool paused = true;

    // Draw some text
    int score = 0;

    sf::Text messageText;
    sf::Text scoreText;

    // We need to choose a font
    Font font;
    font.loadFromFile("../fonts/KOMIKAP_.ttf");

    // Set the font to our message
    messageText.setFont(font);
    scoreText.setFont(font);

    // Assign the actual message
    messageText.setString("Press Enter to start!");
    scoreText.setString("Score = 0");

    // Make it really big
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);

    // Choose a color
    messageText.setColor(Color::White);
    scoreText.setColor(Color::White);

    // Position the text
    FloatRect textRect = messageText.getLocalBounds();

    messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                          textRect.top + textRect.height / 2.0f);

    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

    scoreText.setPosition(20, 20);

    while (window.isOpen())
    {
        /*
        ******************************************************
        Handle the player's input
        ******************************************************
        */

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Start the game
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            paused = false;

            // Reset the time and the score
            score = 0;
            timeRemaining = 6;
        }

        /*
        ******************************************************
        Update the scene
        ******************************************************
        */

        if (!paused)
        {

            // Measure time
            Time dt = clock.restart();

            // Subtract from the amount of time remaining
            timeRemaining -= dt.asSeconds();
            // size up the time bar
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if (timeRemaining <= 0.0f) {
                // Pause the game
                paused = true;

                // Change the message shown to the player
                messageText.setString("Out of time!!");

                // Reposition the text based on its new size
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
            }

            // Setup the beee
            if (!beeActive)
            {
                // How fast is the bee
                srand((int)time(0));
                beeSpeed = (rand() % 200) + 200;

                // How high is the bee
                srand((int)time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(2000, height);
                beeActive = true;
            }
            else
            {
                // Move the bee
                spriteBee.setPosition(spriteBee.getPosition().x -
                                          (beeSpeed * dt.asSeconds()),
                                      spriteBee.getPosition().y);

                // Has the bee reached the right hand edge of the screen?
                if (spriteBee.getPosition().x < -100)
                {
                    // Set it up ready to be a whole new bee next frame
                    beeActive = false;
                }
            }

            // Manage the clouds
            for (int i = 0; i < 3; i++) {
                if (!cloudsActive[i]) {
                    // How fast is the cloud
                    srand((int)time(0) * (i+1) *10);
                    cloudsSpeed[i] = (rand() % 200);

                    // How high is the cloud
                    srand((int)time(0) * (i+1) * 10);
                    float height = (rand() % ((i+1) * 300)) - (150 * (i+1));
                    spriteClouds[i].setPosition(-200, height);
                    cloudsActive[i] = true;
                }
                else
                {
                    spriteClouds[i].setPosition(spriteClouds[i].getPosition().x +
                                                (cloudsSpeed[i] * dt.asSeconds()),
                                            spriteClouds[i].getPosition().y);

                    // Has the clout reached the right hand edge of the screen?
                    if (spriteClouds[i].getPosition().x > 1920)
                    {
                        // Set it up ready to be a whole new cloud next frame
                        cloudsActive[i] = false;
                    }
                
                }
            }

            // Update score text
            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());

        } // End if(!paused)

        /*
        ******************************************************
        Draw the scene
        ******************************************************
        */
        // Clear everything from the last frame
        window.clear();

        // Draw our game scene here
        window.draw(spriteBackground);

        // Draw the clouds
        for (int i = 0; i < 3; i++) {
            window.draw(spriteClouds[i]);
        }

        // Draw the tree
        window.draw(spriteTree);

        // Draw the bee
        window.draw(spriteBee);

        // Draw the score
        window.draw(scoreText);

        // Draw the timebar
        window.draw(timeBar);

        if (paused)
        {
            // Draw our message
            window.draw(messageText);
        }

        // Show everything we just drew
        window.display();
    }

    return 0;
}
