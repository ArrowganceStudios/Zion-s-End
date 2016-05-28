#include "Game.h"
#include "Math.h"
#include <iostream>
#include <fstream>
#include <thread>

Game::~Game()
{
	if(m_pResources)
		delete m_pResources;
}

void Game::Init(sf::RenderWindow &r_TargetWindow)
{
	m_pResources = new Resources();
	m_pRenderTarget = &r_TargetWindow;

	m_pResources->GetGrid()->SetWindowSize(m_pRenderTarget->getSize());
	m_pResources->GetGUI()->SetWindowSize(m_pRenderTarget->getSize());

	LoadMap();
	Enemy* enemy = m_pResources->GetEnemy();
	*enemy = Enemy(m_pResources->GetEnemyGraphics(), m_pResources->GetGrid());
}

void Game::Update(sf::Time deltaTime)
{
	sf::Vector2f mousePos((float)sf::Mouse::getPosition(*m_pRenderTarget).x, (float)sf::Mouse::getPosition(*m_pRenderTarget).y);

	m_pResources->GetEnemy()->Update(deltaTime, m_pResources->GetGrid());

	m_pResources->GetGUI()->Update(deltaTime);
	m_pResources->GetGUI()->RequestMessage("XD", m_pResources->GetEnemy()->GetPosition(), (GUI::MessageType)(rand() % 3));
	m_pResources->GetGUI()->UpdateMoneyValue(rand() % 10000);
	m_pResources->GetGUI()->UpdateHealthValue(rand() % 100);
}

void Game::Render()
{
	m_pRenderTarget->clear();

	//	render

	m_pResources->GetGrid()->Render(*m_pRenderTarget);

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
