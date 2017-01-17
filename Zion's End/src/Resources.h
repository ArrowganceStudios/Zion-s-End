#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "GUI.h"
#include "EnemyManager.h"
#include "TowerManager.h"
#include "ProjectileManager.h"
#include "MoneyManager.h"


class Resources
{
public:
	Resources() = default;
	~Resources() = default;

	Grid*				GetGrid()				{ return &m_Grid; }
	GUI*				GetGUI()				{ return &m_GUI; }
	EnemyManager*		GetEnemyManager()		{ return &m_EnemyManager; }
	TowerManager*		GetTowerManager()		{ return &m_TowerManager; }
	ProjectileManager*	GetProjectileManager()	{ return &m_ProjecitleManager; }
	MoneyManager*		GetMoneyManager()		{ return &m_MoneyManager; }

private:
	//	memory content
	Grid				m_Grid;
	GUI					m_GUI;
	EnemyManager		m_EnemyManager;
	TowerManager		m_TowerManager;
	ProjectileManager	m_ProjecitleManager;
	MoneyManager		m_MoneyManager;
};