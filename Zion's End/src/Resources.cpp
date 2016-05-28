#include "Resources.h"

Resources::Resources() : m_EnemyGraphics("assets/Zombie.png")
{
	m_Enemy.SetGraphicsComponent(&m_EnemyGraphics);
}

Resources::~Resources()
{
}

