#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>

// Constants
// Player
const float playerHeight = 150.0f;
const float playerSpeed = 10.0f;
// Ball
const float ballRadius = 25.0f;
const float maxBallSpeed = 20.0f;
const float minSpeedIncrease = 0.5f;
const float maxSpeedIncrease = 1.1f;

// Move the ball 
void updateBallPosition(sf::CircleShape& ball, sf::Vector2f& ballSpeed) {
    ball.move(ballSpeed);
}

void checkBallCollisions(sf::CircleShape& ball, sf::Vector2f& ballSpeed, int& playerScore, sf::Text& scoreText, const sf::RectangleShape& player, const sf::RenderWindow& window, bool& gameOver) {
    // Detect collision with vertical borders
    if (ball.getPosition().x + ballSpeed.x <= 0) {
        ballSpeed = { 0, 0 };
		gameOver = true;
        scoreText.setString("Game Over");
    }
    else if (ball.getPosition().x + ballSpeed.x + ballRadius * 2 >= window.getSize().x) {
        ballSpeed.x = -ballSpeed.x;
    }

    // Detect collision with horizontal borders
    if (ball.getPosition().y + ballSpeed.y <= 0 || ball.getPosition().y + ball.getRadius() * 2 + ballSpeed.y >= window.getSize().y)
    {
        ballSpeed.y = -ballSpeed.y;
    }

    // Detect collision with player
    if (ball.getPosition().x + ballSpeed.x <= player.getPosition().x + player.getSize().x) {
        if (ball.getPosition().y + ball.getRadius() * 2 + ballSpeed.y >= player.getPosition().y && ball.getPosition().y + ballSpeed.y <= player.getPosition().y + player.getSize().y) {
            ballSpeed.x = -ballSpeed.x;
            playerScore++;
            scoreText.setString(std::to_string(playerScore));

            float randomSpeedIncrease = 0.5f + (std::rand() % 6) / 10.0f;
            ballSpeed.x += (ballSpeed.x > 0 ? randomSpeedIncrease : -randomSpeedIncrease);

            float playerCenterY = player.getPosition().y + player.getSize().y / 2.0f;
            float ballCenterY = ball.getPosition().y + ball.getRadius();
            float relativeIntersectY = ballCenterY - playerCenterY;

            float normalizedIntersectY = relativeIntersectY / (player.getSize().y / 2.0f);

            ballSpeed.y = normalizedIntersectY * 10.0f;
        }
    }
}

// Check input
void handlePlayerInput(sf::RectangleShape& player, float playerSpeed) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.getPosition().y - playerSpeed >= 0) {
        player.move(0, -playerSpeed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player.getPosition().y + playerHeight + playerSpeed <= 750) {
        player.move(0, playerSpeed);
    }
}

// Update score text
void updateScoreText(sf::Text& scoreText, const int playerScore, const sf::RenderWindow& window) {
    scoreText.setString(std::to_string(playerScore));
    scoreText.setPosition(window.getSize().x / 2.0f - scoreText.getGlobalBounds().width / 2, 10);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1080, 750), "Pong SFML", sf::Style::Default);
    window.setFramerateLimit(30);
    window.setActive(true);

    // Font definition
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/bit5x3.ttf"))
    {
        std::cerr << "Erreur : Impossible de charger la police assets/fonts/bit5x3.ttf" << std::endl;
        return -1;
    }

    // Score definition
    int playerScore = 0;
    sf::Text scoreText("", font);
    scoreText.setCharacterSize(100);
    updateScoreText(scoreText, playerScore, window);

    // Player definition
    sf::Vector2f playerPos = { 50.0f, window.getSize().y / 2.0f };
    sf::RectangleShape player(sf::Vector2f(50, playerHeight));
    player.setFillColor(sf::Color::White);
    player.setPosition(playerPos.x, playerPos.y);

    // Ball definition
    sf::CircleShape ball(ballRadius);
    sf::Vector2f ballPos = { window.getSize().x / 2.0f, window.getSize().y / 2.0f };
    ball.setPosition(ballPos.x, ballPos.y);
    sf::Vector2f ballSpeed = { -10.0f, 0 };

    // Game state
    bool gameOver = false;

    while (window.isOpen())
    {
        // Game loop
        if (!gameOver) {
            updateBallPosition(ball, ballSpeed);
            checkBallCollisions(ball, ballSpeed, playerScore, scoreText, player, window, gameOver);
            handlePlayerInput(player, playerSpeed);
            updateScoreText(scoreText, playerScore, window);
        }
        else {
            scoreText.setString("Game Over");
            scoreText.setPosition(window.getSize().x / 2.0f - 200, 0);
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        // Render
        window.clear();
        window.draw(scoreText);
        window.draw(player);
        window.draw(ball);
        window.display();
    }

    return 0;
}