#include <SFML/Graphics.hpp>

int main()
{
	// Create the main window
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	// Create a graphical text to display
    sf::CircleShape shape(100.f);
	// Set the radius of the circle
    shape.setFillColor(sf::Color::Green);

	// Start the game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}