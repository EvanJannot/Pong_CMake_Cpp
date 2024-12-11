#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1080, 750), "Pong SFML", sf::Style::Default);
    window.setFramerateLimit(30);
    window.setActive(true);
	window.setKeyRepeatEnabled(false); 

    //Font definition
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/bit5x3.ttf"))
    {
        std::cerr << "Erreur : Impossible de charger la police assets/fonts/bit5x3.ttf" << std::endl;
        return -1;
    }

    // Score definition
	int playerScore = 0;
	sf::Text scoreText("",font);
    scoreText.setString(std::to_string(playerScore));
    scoreText.setCharacterSize(100);
    scoreText.setColor(sf::Color::White);
	scoreText.setPosition(window.getSize().x / 2.0f, 0);
	
    // Player definition
	const float playerHeight = 150.0f;
	const float playerSpeed = 10.0f;
	sf::Vector2f playerPos = { 50.0f, window.getSize().y / 2.0f };
	sf::RectangleShape player(sf::Vector2f(50, playerHeight));
	player.setFillColor(sf::Color::White);
	player.setPosition(playerPos.x, playerPos.y);

	// Ball definition
	sf::CircleShape ball(25.0f);
	sf::Vector2f ballPos = { window.getSize().x / 2.0f, window.getSize().y / 2.0f };
	ball.setPosition(ballPos.x, ballPos.y);
	sf::Vector2f ballSpeed = { -10.0f, 0 };

    // Game state
    bool gameOver = false;

    while (window.isOpen())
    {

        if (!gameOver) {
            // Update position
            playerPos = player.getPosition();
            ballPos = ball.getPosition();

            // Detect collision with vertical borders
            if (ball.getPosition().x + ballSpeed.x <= 0) {
                ballSpeed = { 0, 0 };
				gameOver = true;
                scoreText.setString("Game Over");
                scoreText.setPosition(window.getSize().x / 2.0f - 200, 0);
            }
            else if (ball.getPosition().x + ballSpeed.x + ball.getRadius() >= window.getSize().x) {
                ballSpeed.x = -ballSpeed.x;
            }

            // Detect collision with horizontal borders
            if (ball.getPosition().y + ballSpeed.y <= 0 || ball.getPosition().y + ball.getRadius() * 2 + ballSpeed.y >= window.getSize().y)
            {
                ballSpeed.y = -ballSpeed.y;

                float randomFactor = (std::rand() % 10 - 5) / 10.0f;
                ballSpeed.x += randomFactor;

                if (std::abs(ballSpeed.x) > 10.0f)
                    ballSpeed.x = (ballSpeed.x > 0) ? 10.0f : -10.0f;
                if (std::abs(ballSpeed.x) < 3.0f)
                    ballSpeed.x = (ballSpeed.x > 0) ? 3.0f : -3.0f;
            }

			// Keep the ball inside the window
            if (ball.getPosition().y + ball.getRadius() * 2 > window.getSize().y)
                ball.setPosition(ball.getPosition().x, window.getSize().y - ball.getRadius() * 2);
            if (ball.getPosition().y < 0)
                ball.setPosition(ball.getPosition().x, 0);

            // Detect collision with player
            if (ball.getPosition().x + ballSpeed.x <= player.getPosition().x + player.getSize().x) {
                if (ball.getPosition().y + ballSpeed.y >= player.getPosition().y && ball.getPosition().y + ballSpeed.y <= player.getPosition().y + player.getSize().y) {
                    ballSpeed.x = -ballSpeed.x;
                    playerScore++;
                    scoreText.setString(std::to_string(playerScore));

                    float playerCenterY = player.getPosition().y + player.getSize().y / 2.0f;
                    float ballCenterY = ball.getPosition().y + ball.getRadius();
                    float relativeIntersectY = ballCenterY - playerCenterY;

					float normalizedIntersectY = relativeIntersectY / (player.getSize().y / 2.0f);

                    ballSpeed.y = normalizedIntersectY * 10.0f;

                    if (std::abs(ballSpeed.x) < 5.0f)
                        ballSpeed.x = (ballSpeed.x > 0 ? 5.0f : -5.0f);
                }
            }

            // Move the ball 
            ball.move(ballSpeed);

            // Check input
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.getPosition().y - playerSpeed >= 0) {
                player.move(0, -playerSpeed);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player.getPosition().y + playerHeight + playerSpeed <= window.getSize().y) {
                player.move(0, playerSpeed);
            }       
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
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