#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	sf::RenderWindow mainWindow(sf::VideoMode(1024, 768), "Zion's End", sf::Style::Close);
	mainWindow.setFramerateLimit(60);
	Game instance;
	instance.Init(mainWindow);

	sf::Clock g_Clock;
	while (mainWindow.isOpen())
	{
		sf::Event event;
		while (mainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				mainWindow.close();
		}

		//instance.Update(g_Clock.restart());
		instance.Update(sf::milliseconds(16));
		instance.Render();
	}

	return 0;
}