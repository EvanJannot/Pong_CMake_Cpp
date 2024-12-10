#include <SFML/Graphics.hpp>

int main()
{
	// Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

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

		// Clear screen
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}