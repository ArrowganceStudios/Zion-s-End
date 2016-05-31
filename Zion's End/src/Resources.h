#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "GUI.h"
#include "Enemy.h"
#include "Tower.h"

constexpr unsigned int MAX_ENEMIES = 128;
constexpr unsigned int MAX_TOWERS  = 32;

class Resources
{
public:
	Resources();
	~Resources();

	Grid*			 GetGrid()			{ return &m_Grid; }
	GUI*			 GetGUI()			{ return &m_GUI; }

	Enemy::Graphics* GetEnemyGraphics() { return &m_EnemyGraphics; }
	uint8			 GetNumOfEnemies()  { return m_nEnemies; }
	Enemy*			 GetEnemies()		{ return m_Enemies; }

	Tower::Graphics* GetTowerGraphics() { return &m_TowerGraphics; }
	uint8			 GetNumOfTowers()	{ return m_nTowers; }
	Tower*			 GetTowers()		{ return m_Towers; }

private:
	//	memory content
	Grid			m_Grid;
	GUI				m_GUI;

	sf::Texture		m_EnemyTexture;
	Enemy::Graphics m_EnemyGraphics;
	uint8			m_nEnemies = MAX_ENEMIES;
	Enemy			m_Enemies[MAX_ENEMIES];

	sf::Texture		m_TowerTexture;
	Tower::Graphics m_TowerGraphics;
	uint8			m_nTowers = MAX_TOWERS;
	Tower			m_Towers[MAX_TOWERS];
};