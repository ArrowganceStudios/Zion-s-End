#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Resources.h"
#include "Grid.h"

class Game
{
public:
	Game() = default;
	~Game();

	Game(const Game&)			 = delete;
	Game& operator=(const Game&) = delete;

	void Init(sf::RenderWindow &r_TargetWindow); // I think it should be moved to constructor so that the destructor can safely delete m_pResources
	void Update(sf::Time deltaTime);
	void Render();

private:
	void LoadMap();

private:
	Resources*			m_pResources;
	sf::RenderWindow*	m_pRenderTarget;
};