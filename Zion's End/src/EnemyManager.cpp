#include "EnemyManager.h"

void EnemyManager::Init(Grid * targetGrid)
{
	m_pTargetGrid = targetGrid;
	m_EnemyTexture.loadFromFile("assets/Zombie.png");

	Enemy::Graphics enemyGraphics(&m_EnemyTexture);
	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		m_EnemyArray[i] = Enemy(enemyGraphics, m_pTargetGrid);
	}
}

void EnemyManager::Update(sf::Time deltaTime)
{
	for (int i = 0; i < MAX_ENEMIES; ++i)
		m_EnemyArray[i].Update(deltaTime, m_pTargetGrid);
}

void EnemyManager::Render(sf::RenderTarget & renderer)
{
	for (int i = 0; i < MAX_ENEMIES; ++i)
		m_EnemyArray[i].Render(renderer);
}

void EnemyManager::SpawnEnemy()
{
	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		if (!m_EnemyArray[i].IsAlive())
		{
			m_EnemyArray[i].ResetPosition(m_pTargetGrid);
			m_EnemyArray[i].SetAlive(true);
			m_EnemyArray[i].SetHealthPoints(100);
			break;
		}
	}
}
