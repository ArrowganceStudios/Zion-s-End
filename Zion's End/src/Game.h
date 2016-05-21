#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Resources.h"

class Game
{
public:
	Game();
	~Game();

	void Init(sf::RenderWindow &r_TargetWindow);
	void Update(sf::Time deltaTime);
	void Render();
	void Shutdown();

private:
	Resources* mp_Resources;
	sf::RenderWindow* mp_RenderTarget;
};