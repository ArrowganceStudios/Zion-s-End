#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "GUI.h"
#include "EnemyManager.h"
#include "Tower.h"

constexpr unsigned int MAX_TOWERS  = 32;

class Resources
{
public:
	Resources();
	~Resources();

	Grid*			 GetGrid()			{ return &m_Grid; }
	GUI*			 GetGUI()			{ return &m_GUI; }
	EnemyManager*	 GetEnemyManager()  { return &m_EnemyManager; }

	Tower::Graphics* GetTowerGraphics() { return &m_TowerGraphics; }
	uint8			 GetNumOfTowers()	{ return m_nTowers; }
	Tower*			 GetTowers()		{ return m_Towers; }

private:
	//	memory content
	Grid			m_Grid;
	GUI				m_GUI;
	EnemyManager	m_EnemyManager;

	sf::Texture		m_TowerTexture;
	Tower::Graphics m_TowerGraphics;
	uint8			m_nTowers = MAX_TOWERS;
	Tower			m_Towers[MAX_TOWERS];
};