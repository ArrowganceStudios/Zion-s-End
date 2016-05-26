#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "GUI.h"

class Resources
{
public:
	Resources();
	~Resources();

	Grid*			 GetGrid()			{ return &m_Grid; }
	GUI*			 GetGUI()			{ return &m_GUI; }

	sf::CircleShape* GetPlayer()		{ return &m_Test; }
	sf::CircleShape* GetEnemyArray()	{ return m_rgTest; }
	int				 GetEnemyCount()	{ return m_nEnemies; }

	float			 GetPlayerVel()		{ return m_PlayerVelocity; }
	float			 GetEnemyVel()		{ return m_EnemyVelocity; }

private:
	//	memory content
	Grid			m_Grid;
	GUI				m_GUI;

	sf::CircleShape m_Test;
	sf::CircleShape m_rgTest[20];
	int				m_nEnemies = 20;
	
	float			m_PlayerVelocity = 120.f;
	float			m_EnemyVelocity = 50.f;
};