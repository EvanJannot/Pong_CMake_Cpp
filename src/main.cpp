#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

int main()
{
	// Create the main window
    sf::Window window(sf::VideoMode(800, 600), "SFML avec sf::Window", sf::Style::Default);

    window.setActive(true);

	window.setKeyRepeatEnabled(false); // disable key repeat

	// Create a graphical text to display
    sf::CircleShape shape(100.f);

	// Set the color of the circle
    shape.setFillColor(sf::Color::Green);

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
                if (event.key.code == sf::Keyboard::Right)
                {
                    //move the glBegin triangle to the right
                    glTranslatef(0.1f, 0.0f, 0.0f);
				}
				else if (event.key.code == sf::Keyboard::Left)
				{
					//move the glBegin triangle to the left
					glTranslatef(-0.1f, 0.0f, 0.0f);
				}
				else if (event.key.code == sf::Keyboard::Up)
				{
					//move the glBegin triangle up
					glTranslatef(0.0f, 0.1f, 0.0f);
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					//move the glBegin triangle down
					glTranslatef(0.0f, -0.1f, 0.0f);
				}
            }
        }

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

        // draw a triangle
        glBegin(GL_TRIANGLES);

		glColor3f(0.0f, 1.0f, 0.0f); // green

		// define the vertices of the triangle
		glVertex2f(-0.5f, -0.5f); // bottom left
		glVertex2f(0.5f, -0.5f); // bottom right
		glVertex2f(0.0f, 0.5f); // top

		// end the drawing
        glEnd();

        window.display();
    }

    return 0;
}