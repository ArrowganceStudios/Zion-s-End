#include "Game.h"
#include "Math.h"
#include <iostream>
#include <fstream>
#include <thread>

Game::~Game()
{
	delete m_pResources;
}

void Game::Init(sf::RenderWindow &r_TargetWindow)
{
	m_pResources = new Resources();
	m_pRenderTarget = &r_TargetWindow;

	LoadMap();
}

void Game::Update(sf::Time deltaTime)
{
	sf::Vector2f mousePos((float)sf::Mouse::getPosition(*m_pRenderTarget).x, (float)sf::Mouse::getPosition(*m_pRenderTarget).y);
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
	if (m_pResources->GetGrid()->GetTileAtPixel(mousePos.x, mousePos.y, 
		m_pRenderTarget->getSize().x, m_pRenderTarget->getSize().y).type == Grid::Tile::Type::START_TILE)
	{
		std::cout << "On starting tile" << std::endl;
	}
	// Reload map on F1 (to be removed along with <thread> include)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
	{
		LoadMap();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	m_pResources->GetEnemy()->Update(deltaTime);

	m_pResources->GetGUI()->Update(deltaTime);
	m_pResources->GetGUI()->RequestMessage("XD", { float(rand() % 1024), float(rand() % 768) }, (GUI::MessageType)(rand() % 3));
	m_pResources->GetGUI()->UpdateMoneyValue(rand() % 10000);
	m_pResources->GetGUI()->UpdateHealthValue(rand() % 100);
}

void Game::Render()
{
	m_pRenderTarget->clear();

	//	render

	m_pResources->GetGrid()->Render(*m_pRenderTarget);

	m_pRenderTarget->draw(*m_pResources->GetPlayer());
	for (int i = 0; i < m_pResources->GetEnemyCount(); ++i)
		m_pRenderTarget->draw(m_pResources->GetEnemyArray()[i]);

	m_pResources->GetEnemy()->Render(*m_pRenderTarget);

	m_pResources->GetGUI()->Render(*m_pRenderTarget);
	//	endrender

	m_pRenderTarget->display();
}

void Game::LoadMap()
{
	std::ifstream mapFile("assets/map0.map");
	unsigned int j = 0;

	for (std::string line; std::getline(mapFile, line); ++j)
	{
		for (unsigned int i = 0; i < line.size(); ++i)
		{
			Grid::Tile::Type type = (Grid::Tile::Type) (line[i] - '0');
			m_pResources->GetGrid()->SetTypeOfTileAt(j, i, type);
		}
	}
}
