#pragma once
#include "Enemy.h"

constexpr unsigned int MAX_ENEMIES = 16;

class EnemyManager
{
public:
	void Init(Resources* resources);

	void Update(sf::Time deltaTime);
	void Render(sf::RenderTarget & renderer);

	void SpawnEnemy(/*enemy type?*/);

	Enemy& operator[](unsigned int index) { return m_EnemyArray[index % MAX_ENEMIES]; }	//	changing to ordinary method? to discuss

private:
	Resources* m_pResources;

	Enemy m_EnemyArray[MAX_ENEMIES];
	sf::Texture m_EnemyTexture;
};