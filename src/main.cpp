#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

int main()
{
	// Create the main window
    sf::Window window(sf::VideoMode(1080, 720), "SFML avec sf::Window", sf::Style::Default);

    window.setActive(true);

	window.setKeyRepeatEnabled(false); // disable key repeat

	float playerPosY = 0.0f; 
	const float playerHeight = 0.3f;
	const float playerSpeed = 0.1f;

    // run the program as long as the window is open
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
                    if (playerPosY + playerHeight + playerSpeed <= 1.0f)
                        playerPosY += playerSpeed;
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
                    if (playerPosY - playerHeight - playerSpeed >= -1.0f)
                        playerPosY -= playerSpeed;
				}
            }
        }

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

        // draw a quad
        glBegin(GL_QUADS);

		glColor3f(1.0f, 1.0f, 1.0f);  // white color

        // Vertices for the Pong player (left side of the screen)
        glVertex2f(-0.95f, playerPosY - playerHeight); // bottom left
        glVertex2f(-0.95f, playerPosY + playerHeight);  // top left
        glVertex2f(-0.90f, playerPosY + playerHeight);  // top right
        glVertex2f(-0.90f, playerPosY - playerHeight); // bottom right


		// end the drawing
        glEnd();

        window.display();
    }

    return 0;
}