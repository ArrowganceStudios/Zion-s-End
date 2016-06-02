#pragma once
#include "Enemy.h"

constexpr unsigned int MAX_ENEMIES = 16;

class EnemyManager
{
public:
	void Init(Grid* targetGrid);

	void Update(sf::Time deltaTime);
	void Render(sf::RenderTarget & renderer);

	void SpawnEnemy(/*enemy type?*/);

	Enemy& operator[](unsigned int index) { return m_EnemyArray[index % MAX_ENEMIES]; }	//	changing to ordinary method? to discuss

private:
	Grid* m_pTargetGrid;

	Enemy m_EnemyArray[MAX_ENEMIES];
	sf::Texture m_EnemyTexture;
};