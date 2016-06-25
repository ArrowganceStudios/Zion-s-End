#include "Game.h"
#include "Math.h"
#include "Tower.h"
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
	m_pResources->GetEnemyManager()->Init(m_pResources->GetGrid());
	m_pResources->GetTowerManager()->Init(m_pResources->GetGrid());

	LoadMap("assets/map0.map");
}

void Game::Update(sf::Time deltaTime)
{
	static sf::Time timer;
	static sf::Time enemySpawnTimer;

	sf::Vector2f mousePos((float)sf::Mouse::getPosition(*m_pRenderTarget).x, (float)sf::Mouse::getPosition(*m_pRenderTarget).y);

	m_pResources->GetGUI()->Update(deltaTime);
	//temp
	if (timer.asSeconds() > 1.f)
	{
		for (int i = 0; i < MAX_ENEMIES; ++i)
		{
			Enemy& enemyRef = (*m_pResources->GetEnemyManager())[i];
			if (enemyRef.IsAlive())
			{
				uint8 damage = rand() % 15;
				enemyRef.Damage(damage);
				m_pResources->GetGUI()->RequestMessage("-" + std::to_string(damage), enemyRef.GetPosition(), GUI::MessageType::NEGATIVE);
			}
		}
		
		
		timer -= sf::seconds(1.f);
	}
	m_pResources->GetGUI()->UpdateMoneyValue(rand() % 10000);
	m_pResources->GetGUI()->UpdateHealthValue(rand() % 100);

	//temp
	if (enemySpawnTimer.asSeconds() > 0.5f)
	{
		m_pResources->GetEnemyManager()->SpawnEnemy();
		enemySpawnTimer -= sf::seconds(0.5f);
	}
	//temp
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		auto tile = m_pResources->GetGrid()->GetTileAtPixel(mousePos.x, mousePos.y);
		auto gridWidth = m_pResources->GetGrid()->GetGridWidth();
		m_pResources->GetTowerManager()->SpawnTower(tile.index / gridWidth, tile.index % gridWidth);
	}
	
	m_pResources->GetEnemyManager()->Update(deltaTime);
	m_pResources->GetTowerManager()->Update(deltaTime);

	timer += deltaTime;
	enemySpawnTimer += deltaTime;
}

void Game::Render()
{
	m_pRenderTarget->clear();

	//	render
	m_pResources->GetGrid()->Render(*m_pRenderTarget);
	m_pResources->GetEnemyManager()->Render(*m_pRenderTarget);
	m_pResources->GetTowerManager()->Render(*m_pRenderTarget);
	m_pResources->GetGUI()->Render(*m_pRenderTarget);
	//	endrender

	m_pRenderTarget->display();
}

void Game::LoadMap(const char* pathToMap)
{
	std::ifstream mapFile(pathToMap);
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
