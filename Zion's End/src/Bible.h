#pragma once
#include "LiteralTypes.h"

class Bible
{
public:
	Bible()						 : m_Health(DEFAULT_MAX_HEALTH), m_Alive(true) {}

	void		 Init(sf::Vector2f position, uint16 health) { m_Position = position; m_Health = health; }

	void		 TakeDamage(uint16 damage)	{ if (damage >= m_Health) m_Alive = false; else m_Health -= damage; }

	void		 SetAlive(bool status)		{ m_Alive = status; }
	bool		 IsAlive() const				{ return m_Alive; }

	uint16		 GetHealth() const			{ return m_Health; }
	sf::Vector2f GetPosition() const	{ return m_Position; }

private:
	sf::Vector2f m_Position;
	uint16		 m_Health;
	bool		 m_Alive;

	static constexpr uint16 DEFAULT_MAX_HEALTH = 1000;
};