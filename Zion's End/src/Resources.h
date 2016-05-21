#pragma once
#include <SFML/Graphics.hpp>

class Resources
{
public:
	Resources();
	~Resources();

	sf::CircleShape *GetPlayer()		{ return &m_Test; }
	sf::CircleShape *GetEnemyArray()	{ return m_rgTest; }
	int GetEnemyCount()					{ return m_EnemyCount; }

	float GetPlayerVel()				{ return m_PlayerVelocity; }
	float GetEnemyVel()					{ return m_EnemyVelocity; }

private:
	//	memory content
	sf::CircleShape m_Test;
	sf::CircleShape m_rgTest[20];
	int m_EnemyCount = 20;
	
	float m_PlayerVelocity = 120.f;
	float m_EnemyVelocity = 50.f;
};