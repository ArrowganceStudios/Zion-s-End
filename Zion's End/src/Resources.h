#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "GUI.h"
#include "Enemy.h"

class Resources
{
public:
	Resources();
	~Resources();

	Grid*			 GetGrid()			{ return &m_Grid; }
	GUI*			 GetGUI()			{ return &m_GUI; }
	Enemy*			 GetEnemy()			{ return &m_Enemy; }
	Enemy::Graphics* GetEnemyGraphics() { return &m_EnemyGraphics; }

private:
	//	memory content
	Grid			m_Grid;
	GUI				m_GUI;
	Enemy			m_Enemy;
	Enemy::Graphics m_EnemyGraphics;
};