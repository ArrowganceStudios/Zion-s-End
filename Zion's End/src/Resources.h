#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "GUI.h"
#include "EnemyManager.h"
#include "TowerManager.h"

class Resources
{
public:
	Resources();
	~Resources();

	Grid*			GetGrid()			{ return &m_Grid; }
	GUI*			GetGUI()			{ return &m_GUI; }
	EnemyManager*	GetEnemyManager()	{ return &m_EnemyManager; }
	TowerManager*	GetTowerManager()	{ return &m_TowerManager; }

private:
	//	memory content
	Grid			m_Grid;
	GUI				m_GUI;
	EnemyManager	m_EnemyManager;
	TowerManager	m_TowerManager;

};