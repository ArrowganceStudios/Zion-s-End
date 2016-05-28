#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "GUI.h"
#include "Enemy.h"

constexpr unsigned int MAX_ENEMIES = 128;

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

private:
	//	memory content
	Grid			m_Grid;
	GUI				m_GUI;

	Enemy::Graphics m_EnemyGraphics;
	uint8			m_nEnemies = MAX_ENEMIES;
	Enemy			m_Enemies[MAX_ENEMIES];
};