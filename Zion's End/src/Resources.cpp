#include "Resources.h"

Resources::Resources()
{
	m_TowerTexture.loadFromFile("assets/TowerSpriteSheet.png");
	m_TowerGraphics.SetTexture(&m_TowerTexture);
}

Resources::~Resources()
{
}

