#include "Resources.h"

Resources::Resources()
{
	m_EnemyTexture.loadFromFile("assets/Zombie.png");
	m_EnemyGraphics.SetTexture(&m_EnemyTexture);

	const sf::Vector2f initialEnemyPosition = { 0.0f, 0.0f };
	Enemy* enemy = m_Enemies;
	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		*enemy = Enemy();
		++enemy;
	}
}

Resources::~Resources()
{
}

