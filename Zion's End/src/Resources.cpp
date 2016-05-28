#include "Resources.h"

Resources::Resources() : m_EnemyGraphics("assets/Zombie.png")
{
	m_Enemy.SetGraphicsComponent(&m_EnemyGraphics);

	m_Test.setPosition(200, 200);
	m_Test.setFillColor(sf::Color::Green);
	m_Test.setRadius(20);

	for (int i = 0; i < m_nEnemies; ++i)
	{
		m_rgTest[i].setPosition((float)(rand() % 1024), (float)(rand() % 768));
		m_rgTest[i].setFillColor(sf::Color::Red);
		m_rgTest[i].setRadius(20);
	}
}

Resources::~Resources()
{
}

