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
	m_pResources->GetEnemyManager()->Init(m_pResources);
	m_pResources->GetTowerManager()->Init(m_pResources);
	m_pResources->GetProjectileManager()->Init();

	LoadMap("assets/map0.map");
}

void Game::Update(sf::Time deltaTime)
{
	static sf::Time timer;
	static sf::Time enemySpawnTimer;

	sf::Vector2f mousePos((float)sf::Mouse::getPosition(*m_pRenderTarget).x, (float)sf::Mouse::getPosition(*m_pRenderTarget).y);

	m_pResources->GetGUI()->Update(deltaTime);

	//	TODO: Get the dimensions in some smarter way
	constexpr float enemyRadius = 64;
	constexpr float projectileRadius = 30;
	constexpr float radiiSum = enemyRadius + projectileRadius;

	for (int i = 0; i < MAX_PROJECTILES; ++i)
	{
		auto& curProj = (*m_pResources->GetProjectileManager())[i];
		if (!curProj.IsAlive())
			continue;

		for (int j = 0; j < MAX_ENEMIES; ++j)
		{
			auto& curEn = (*m_pResources->GetEnemyManager())[j];
			if (!curEn.IsAlive())
				continue;

			bool collision = radiiSum > as::Length(curProj.GetPosition() - curEn.GetPosition());

			if (collision)
			{

				curProj.Collide();
				curEn.Damage(curProj.GetDamage(), m_pResources);
				m_pResources->GetGUI()->RequestMessage("-" + std::to_string(curProj.GetDamage()), curEn.GetPosition(), GUI::MessageType::NEGATIVE);
			}

		}

	}

	m_pResources->GetGUI()->UpdateMoneyValue(m_pResources->GetMoneyManager()->GetMoney());
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
		if (m_pResources->GetMoneyManager()->GetMoney() >= 500)
		{
			auto tile = m_pResources->GetGrid()->GetTileAtPixel(mousePos.x, mousePos.y);
			auto gridWidth = m_pResources->GetGrid()->GetGridWidth();
			m_pResources->GetTowerManager()->SpawnTower(tile.index / gridWidth, tile.index % gridWidth);
			m_pResources->GetMoneyManager()->SubtractMoney(500);
		}
	}
	
	m_pResources->GetEnemyManager()->Update(deltaTime);
	m_pResources->GetTowerManager()->Update(deltaTime);
	m_pResources->GetProjectileManager()->Update(deltaTime);

	timer += deltaTime;
	enemySpawnTimer += deltaTime;
}

void Game::Render()
{
	m_pRenderTarget->clear();

	//	render
	m_pResources->GetGrid()->Render(*m_pRenderTarget);
	m_pResources->GetEnemyManager()->Render(*m_pRenderTarget);
	m_pResources->GetProjectileManager()->Render(*m_pRenderTarget);
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
