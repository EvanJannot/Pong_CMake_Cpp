#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>

// Constants
// Player
const float playerHeight = 150.0f;
const float playerSpeed = 15.0f;
// Ball
const float ballRadius = 25.0f;
const float maxBallSpeed = 20.0f;
const float minSpeedIncrease = 0.5f;
const float maxSpeedIncrease = 1.1f;

// Move the ball 
void updateBallPosition(sf::CircleShape& ball, sf::Vector2f& ballSpeed) {
    ball.move(ballSpeed);
}

// Check ball collisions with borders and player
void checkBallCollisions(sf::CircleShape& ball, sf::Vector2f& ballSpeed, int& player1Score, int& player2Score,
    sf::Text& score1Text, sf::Text& score2Text, const sf::RectangleShape& player1, const sf::RectangleShape& player2,
    const sf::RenderWindow& window, bool& gameOver) 
{
    // Detect collision with vertical borders
	if (ball.getPosition().x + ballSpeed.x <= 0) { // If ball goes behind player 1
        ballSpeed = { 0, 0 };
		gameOver = true;
    }
	else if (ball.getPosition().x + ballSpeed.x + ballRadius * 2 >= window.getSize().x) { // If ball goes behind player 2
        ballSpeed = { 0, 0 };
        gameOver = true;
    }

    // Detect collision with horizontal borders
    if (ball.getPosition().y + ballSpeed.y <= 0 || ball.getPosition().y + ball.getRadius() * 2 + ballSpeed.y >= window.getSize().y) 
    {
        ballSpeed.y = -ballSpeed.y;
    }

    // Detect collision with player 1
    if (ball.getPosition().x + ballSpeed.x <= player1.getPosition().x + player1.getSize().x) {
        if (ball.getPosition().y + ball.getRadius() * 2 + ballSpeed.y >= player1.getPosition().y && ball.getPosition().y + ballSpeed.y <= player1.getPosition().y + player1.getSize().y) {
            
            ballSpeed.x = -ballSpeed.x;
            player1Score++;
            score1Text.setString(std::to_string(player1Score));

			float randomSpeedIncrease = 0.5f + (std::rand() % 6) / 10.0f; // Random speed increase between 0.5 and 1.1
			ballSpeed.x += (ballSpeed.x > 0 ? randomSpeedIncrease : -randomSpeedIncrease); // Increase ball speed

			float playerCenterY = player1.getPosition().y + player1.getSize().y / 2.0f; // Get player center
			float ballCenterY = ball.getPosition().y + ball.getRadius(); // Get ball center
			float relativeIntersectY = ballCenterY - playerCenterY; // Get distance between ball and player center

			float normalizedIntersectY = relativeIntersectY / (player1.getSize().y / 2.0f); // Normalize distance between ball and player center between -1 and 1

			ballSpeed.y = normalizedIntersectY * 10.0f; // Set vertical ball speed according to distance between ball and player center
        }
	}
	else if (ball.getPosition().x + ballSpeed.x + ball.getRadius() * 2 >= player2.getPosition().x) { // Detect collision with player 2
		if (ball.getPosition().y + ball.getRadius() * 2 + ballSpeed.y >= player2.getPosition().y && ball.getPosition().y + ballSpeed.y <= player2.getPosition().y + player2.getSize().y) 
        {
			ballSpeed.x = -ballSpeed.x;
			player2Score++;
			score2Text.setString(std::to_string(player2Score));

            float randomSpeedIncrease = 0.5f + (std::rand() % 6) / 10.0f; // Random speed increase between 0.5 and 1.1
            ballSpeed.x += (ballSpeed.x > 0 ? randomSpeedIncrease : -randomSpeedIncrease); // Increase ball speed

            float playerCenterY = player1.getPosition().y + player1.getSize().y / 2.0f; // Get player center
            float ballCenterY = ball.getPosition().y + ball.getRadius(); // Get ball center
            float relativeIntersectY = ballCenterY - playerCenterY; // Get distance between ball and player center

            float normalizedIntersectY = relativeIntersectY / (player1.getSize().y / 2.0f); // Normalize distance between ball and player center between -1 and 1

            ballSpeed.y = normalizedIntersectY * 10.0f; // Set vertical ball speed according to distance between ball and player center
		}
	}
}                                                                               

// Check input
void handlePlayerInput(sf::RectangleShape& player1, sf::RectangleShape& player2, float playerSpeed) {
	// Player 1 controls
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player1.getPosition().y - playerSpeed >= 0) {
        player1.move(0, -playerSpeed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player1.getPosition().y + player1.getSize().y + playerSpeed <= 750) {
        player1.move(0, playerSpeed);
    }

	// Player 2 controls
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player2.getPosition().y - playerSpeed >= 0) {
        player2.move(0, -playerSpeed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player2.getPosition().y + player2.getSize().y + playerSpeed <= 750) {
        player2.move(0, playerSpeed);
    }
}

// Update score text
void updateScoreText(sf::Text& scoreText, const int playerScore, const sf::RenderWindow& window) {
    scoreText.setString(std::to_string(playerScore));
}

int main()
{
	// Window definition
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

	// Game over text definition
    sf::Text gameOverText("", font);
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over");
    gameOverText.setPosition(window.getSize().x / 2.0f - gameOverText.getGlobalBounds().width / 2,
        window.getSize().y / 2.0f - gameOverText.getGlobalBounds().height / 2);


    // Score definition
    int player1Score = 0;
    sf::Text score1Text("", font);
    score1Text.setCharacterSize(100);
    updateScoreText(score1Text, player1Score, window);
	int player2Score = 0;
	sf::Text score2Text("", font);
	score2Text.setCharacterSize(100);
	updateScoreText(score2Text, player2Score, window);
	score1Text.setPosition(window.getSize().x / 3.0f - score1Text.getGlobalBounds().width / 2, 10);
	score2Text.setPosition(2* window.getSize().x / 3.0f + score2Text.getGlobalBounds().width / 2, 10);

    // Player 1 definition
    sf::Vector2f player1Pos = { 50.0f, window.getSize().y / 2.0f };
    sf::RectangleShape player1(sf::Vector2f(50, playerHeight));
    player1.setFillColor(sf::Color::White);
    player1.setPosition(player1Pos.x, player1Pos.y);

	// Player 2 definition
	sf::Vector2f player2Pos = { window.getSize().x - 100.0f, window.getSize().y / 2.0f };
	sf::RectangleShape player2(sf::Vector2f(50, playerHeight));
	player2.setFillColor(sf::Color::White);
	player2.setPosition(player2Pos.x, player2Pos.y);

    // Ball definition
    sf::CircleShape ball(ballRadius);
    sf::Vector2f ballPos = { window.getSize().x / 2.0f, window.getSize().y / 2.0f };
    ball.setPosition(ballPos.x, ballPos.y);
    sf::Vector2f ballSpeed = { -10.0f, 0 };

    // Game state
    bool gameOver = false;

	// Game loop
    while (window.isOpen())
    {
        if (!gameOver) {
            updateBallPosition(ball, ballSpeed);
            checkBallCollisions(ball, ballSpeed, player1Score, player2Score, score1Text, score2Text, player1, player2, window, gameOver);
            handlePlayerInput(player1, player2, playerSpeed);
            updateScoreText(score1Text, player1Score, window);
			updateScoreText(score2Text, player2Score, window);
        }

		// Event handling
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