#pragma once
#include "Tower.h"

constexpr unsigned int MAX_TOWERS = 16;

class Resources;

class TowerManager
{
public:
	void Init(Resources* targetResources);

	void Update(sf::Time deltaTime);
	void Render(sf::RenderTarget &renderer);

	void SpawnTower(uint8 tileIdxX, uint8 tileIdxY);

	Tower& operator[](unsigned int index) { return m_TowerArray[index % MAX_TOWERS]; }

private:
	Resources* m_pResources;

	Tower m_TowerArray[MAX_TOWERS];
	sf::Texture m_TowerTexture;
};