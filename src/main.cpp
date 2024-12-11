#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>

// Constants
// Window
const int windowWidth = 1080;
const int windowHeight = 750;
// Player
const float playerHeight = 150.0f;
const float playerWidth = 50.0f;
const float playerSpeed = 15.0f;
// Ball
const float ballRadius = 25.0f;
const float initialBallSpeedX = -10.0f;
const float maxBallSpeed = 20.0f;
const float minSpeedIncrease = 0.5f;
const float maxSpeedIncrease = 1.1f;
// Font
const int fontSize = 100;
// Dashed line
const float dashWidth = 5.0f;
const float dashHeight = 20.0f;
const float dashSpacing = 10.0f;

// Move the ball 
void updateBallPosition(sf::CircleShape& ball, sf::Vector2f& ballSpeed) {
    ball.move(ballSpeed);
}

// Handle collision of the ball with the top and bottom borders
void handleBallBorderCollision(sf::CircleShape& ball, sf::Vector2f& ballSpeed) {
    if (ball.getPosition().y <= 0 || ball.getPosition().y + ball.getRadius() * 2 >= windowHeight) {
        ballSpeed.y = -ballSpeed.y; // Reverse the vertical direction
    }
}

// Handle collision of the ball with a player paddle
void handleBallPlayerCollision(sf::CircleShape& ball,
                               sf::Vector2f& ballSpeed,
                               const sf::RectangleShape& player,
                               int& playerScore,
                               sf::Text& scoreText)
{   
    // Check collision with the paddle
    if (ball.getGlobalBounds().intersects(player.getGlobalBounds()))
    {
            ballSpeed.x = -ballSpeed.x; // Reverse horizontal direction

            // Increment the player's score
            playerScore++;
            scoreText.setString(std::to_string(playerScore));

			// Increase horizontal ball speed
            float randomSpeedIncrease = minSpeedIncrease + (std::rand() % static_cast<int>((maxSpeedIncrease - minSpeedIncrease) * 10)) / 10.0f;
			ballSpeed.x += (ballSpeed.x > 0 ? randomSpeedIncrease : -randomSpeedIncrease); 

            // Adjust vertical ball speed based on impact position
			float playerCenterY = player.getPosition().y + player.getSize().y / 2.0f; // Get player center
			float ballCenterY = ball.getPosition().y + ball.getRadius(); // Get ball center
			float relativeIntersectY = ballCenterY - playerCenterY; // Get distance between ball and player center
			float normalizedIntersectY = relativeIntersectY / (player.getSize().y / 2.0f); // Normalize distance between ball and player center between -1 and 1

			ballSpeed.y = normalizedIntersectY * 10.0f; // Set vertical ball speed according to distance between ball and player center
	}
}   

// Check all ball collisions
void checkBallCollisions(sf::CircleShape& ball,
                        sf::Vector2f& ballSpeed,
                        const sf::RectangleShape& player1,
                        const sf::RectangleShape& player2,
                        int& player1Score,
                        sf::Text& score1Text,
                        int& player2Score,
                        sf::Text& score2Text,
                        bool& gameOver)
{
    // Check collision with borders
    handleBallBorderCollision(ball, ballSpeed);

    // Check if the ball goes out of bounds
    if (ball.getPosition().x <= 0 || ball.getPosition().x + ball.getRadius() * 2 >= windowWidth) {
        gameOver = true;
        ballSpeed = { 0, 0 }; // Stop the ball
        return;
    }

    // Check collision with players
    handleBallPlayerCollision(ball, ballSpeed, player1, player1Score, score1Text);
    handleBallPlayerCollision(ball, ballSpeed, player2, player2Score, score2Text);
}

// Handle player input
void handlePlayerInput(sf::RectangleShape& player1, sf::RectangleShape& player2) {
	// Player 1 controls (W and S)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player1.getPosition().y - playerSpeed >= 0) {
        player1.move(0, -playerSpeed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player1.getPosition().y + player1.getSize().y + playerSpeed <= 750) {
        player1.move(0, playerSpeed);
    }

    // Player 2 controls (Arrow keys)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player2.getPosition().y - playerSpeed >= 0) {
        player2.move(0, -playerSpeed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player2.getPosition().y + player2.getSize().y + playerSpeed <= 750) {
        player2.move(0, playerSpeed);
    }
}

// Update the score text
void updateScoreText(sf::Text& scoreText, const int score, const float xPosition) {
    scoreText.setString(std::to_string(score));
    scoreText.setPosition(xPosition, 10);
}

// Main function
int main()
{
    // Create a window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Pong SFML");
    window.setFramerateLimit(30);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/bit5x3.ttf"))
    {
        std::cerr << "Error: Could not load font." << std::endl;
        return -1;
    }

    // Game state variables
    bool gameOver = false;

    // Initialize scores
    int player1Score = 0;
    int player2Score = 0;

    // Create score texts
    sf::Text score1Text("", font, fontSize);
    sf::Text score2Text("", font, fontSize);
    updateScoreText(score1Text, player1Score, windowWidth / 3.0f);
    updateScoreText(score2Text, player2Score, 2 * windowWidth / 3.0f);

    // Create "Game Over" text
    sf::Text gameOverText("Game Over", font, fontSize);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(windowWidth / 2.0f - gameOverText.getGlobalBounds().width / 2,
        windowHeight / 2.0f - gameOverText.getGlobalBounds().height / 2);

    // Create player paddles
    sf::RectangleShape player1(sf::Vector2f(playerWidth, playerHeight));
    player1.setPosition(50.0f, windowHeight / 2.0f - playerHeight / 2.0f);

    sf::RectangleShape player2(sf::Vector2f(playerWidth, playerHeight));
    player2.setPosition(windowWidth - 100.0f, windowHeight / 2.0f - playerHeight / 2.0f);

    // Create ball
    sf::CircleShape ball(ballRadius);
    ball.setPosition(windowWidth / 2.0f - ballRadius, windowHeight / 2.0f - ballRadius);
    sf::Vector2f ballSpeed(initialBallSpeedX, 0);

	// Game loop
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        // Update game logic
        if (!gameOver) {
            updateBallPosition(ball, ballSpeed);
            checkBallCollisions(ball, ballSpeed, player1, player2, player1Score, score1Text, player2Score, score2Text, gameOver);
            handlePlayerInput(player1, player2);
        }

        // Render
        window.clear();

        // Draw the dashed line
        for (float y = 0; y < windowHeight; y += dashHeight + dashSpacing) {
            sf::RectangleShape dash(sf::Vector2f(dashWidth, dashHeight));
            dash.setPosition(windowWidth / 2.0f - dashWidth / 2.0f, y);
            window.draw(dash);
        }

        // Draw other elements
        window.draw(score1Text);
		window.draw(score2Text);
        window.draw(player1);
		window.draw(player2);
        window.draw(ball);
        if (gameOver)
        {
            window.draw(gameOverText);
        }
        window.display();



    }

    return 0;
}