#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1080, 750), "Pong SFML", sf::Style::Default);
    window.setFramerateLimit(30);
    window.setActive(true);
	window.setKeyRepeatEnabled(false); 
	
    // Player definition
	const float playerHeight = 150.0f;
	const float playerSpeed = 50.0f;
	sf::Vector2f playerPos = { 50.0f, window.getSize().y - playerHeight };
	sf::RectangleShape player(sf::Vector2f(50, playerHeight));
	player.setFillColor(sf::Color::White);
	player.setPosition(playerPos.x, playerPos.y);

	// Ball definition
	sf::CircleShape ball(25.0f);
	sf::Vector2f ballPos = { window.getSize().x / 2.0f, window.getSize().y / 2.0f };
	ball.setPosition(ballPos.x, ballPos.y);

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up && player.getPosition().y - playerSpeed >= 0)
                {
                    playerPos.y -= playerSpeed;
                    player.setPosition(playerPos.x, playerPos.y);
                }
                else if (event.key.code == sf::Keyboard::Down && player.getPosition().y + playerHeight + playerSpeed <= window.getSize().y)
                {
                    playerPos.y += playerSpeed;
                    player.setPosition(playerPos.x, playerPos.y);
                }
            }
        }

        window.clear();

        window.draw(player);
		window.draw(ball);

        window.display();
    }

    return 0;
}