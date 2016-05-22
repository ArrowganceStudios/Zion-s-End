#include "Game.h"
#include "Math.h"
#include <iostream>

Game::~Game()
{
	delete m_pResources;
}

void Game::Init(sf::RenderWindow &r_TargetWindow)
{
	m_pResources = new Resources();
	m_pRenderTarget = &r_TargetWindow;

	// Debug
	m_pResources->GetGrid()->SetTypeOfTileAt(0, 0, Grid::Tile::Type::START_TILE);
	m_pResources->GetGrid()->SetTypeOfTileAt(0, 1, Grid::Tile::Type::START_TILE);
	m_pResources->GetGrid()->SetTypeOfTileAt(0, 2, Grid::Tile::Type::START_TILE);
}

void Game::Update(sf::Time deltaTime)
{
	sf::Vector2f mousePos(sf::Mouse::getPosition(*m_pRenderTarget).x, sf::Mouse::getPosition(*m_pRenderTarget).y);
	auto p_Player = m_pResources->GetPlayer();
	auto p_Enemies = m_pResources->GetEnemyArray();

	sf::Vector2f directionToMouse = as::Direction(p_Player->getPosition(), mousePos);
	p_Player->move(directionToMouse * deltaTime.asSeconds() * m_pResources->GetPlayerVel());

	for (int i = 0; i < m_pResources->GetEnemyCount(); ++i)
	{
		sf::Vector2f directionToPlayer = as::Direction(p_Enemies[i].getPosition(), p_Player->getPosition());
		p_Enemies[i].move(directionToPlayer * deltaTime.asSeconds() * m_pResources->GetEnemyVel());
	}

	// Debug
	if (m_pResources->GetGrid()->GetTileAtPixel(mousePos.x, mousePos.y, 1024, 768).type == Grid::Tile::Type::START_TILE)
		std::cout << "On starting tile" << std::endl;

}

void Game::Render()
{
	m_pRenderTarget->clear();

	//	render
	// TODO fix the magic numbers (resolution)
	float tileWidth = m_pResources->GetGrid()->GetTileWidth(1024);
	float tileHeight = m_pResources->GetGrid()->GetTileHeight(768);

	uint8 gridWidth = m_pResources->GetGrid()->GetGridWidth();
	uint8 gridHeight = m_pResources->GetGrid()->GetGridHeight();

	for (int i = 0; i < gridHeight; ++i)
	{
		for (int j = 0; j < gridWidth; ++j)
		{
			sf::RectangleShape rect({ tileWidth, tileHeight });
			if ((i * (2 * gridWidth + 1) + j) % 2)
				rect.setFillColor(sf::Color::Black);
			else
				rect.setFillColor(sf::Color::White);
			rect.setPosition({ j * tileWidth, i * tileHeight });
			m_pRenderTarget->draw(rect);
		}
	}

	m_pRenderTarget->draw(*m_pResources->GetPlayer());
	for (int i = 0; i < m_pResources->GetEnemyCount(); ++i)
		m_pRenderTarget->draw(m_pResources->GetEnemyArray()[i]);

	//	endrender

	m_pRenderTarget->display();
}