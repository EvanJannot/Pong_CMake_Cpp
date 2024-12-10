#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

int main()
{
	// Create the main window
    sf::Window window(sf::VideoMode(800, 600), "SFML avec sf::Window", sf::Style::Default);

    window.setActive(true);

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
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); 
        glVertex2f(-0.5f, -0.5f);

        glColor3f(0.0f, 1.0f, 0.0f); 
        glVertex2f(0.5f, -0.5f);

        glColor3f(0.0f, 0.0f, 1.0f); 
        glVertex2f(0.0f, 0.5f);
        glEnd();

        window.display();
    }

    return 0;
}