#include "Resources.h"

Resources::Resources()
{
	m_EnemyTexture.loadFromFile("assets/Zombie.png");
	m_EnemyGraphics.SetTexture(&m_EnemyTexture);

	m_TowerTexture.loadFromFile("assets/TowerSpriteSheet.png");
	m_TowerGraphics.SetTexture(&m_TowerTexture);
}

Resources::~Resources()
{
}

