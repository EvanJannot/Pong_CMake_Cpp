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
	
	const float playerHeight = 150.0f;
	const float playerSpeed = 50.0f;

    float playerPosY = window.getSize().y - playerHeight;
    float playerPosX = 50.0f;

	sf::RectangleShape player(sf::Vector2f(50, playerHeight));
	player.setFillColor(sf::Color::White);
	player.setPosition(playerPosX, playerPosY);

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
				if (event.key.code == sf::Keyboard::Up)
				{
                    if (player.getPosition().y - playerSpeed >= 0)
                    {
                        playerPosY -= playerSpeed;
                        player.setPosition(playerPosX, playerPosY);
                    }
                        
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
                    if (player.getPosition().y + playerHeight + playerSpeed  <= window.getSize().y)
                    {
                        playerPosY += playerSpeed;
                        player.setPosition(playerPosX, playerPosY);
                    }
				}
            }
        }
        window.clear();

        window.draw(player);

        window.display();
    }

    return 0;
}