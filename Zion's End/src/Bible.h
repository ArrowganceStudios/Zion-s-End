#pragma once
#include "LiteralTypes.h"

class Bible
{
public:
	enum class Status
	{
		ALIVE,
		DEAD
	};

public:
	Bible()					: m_Health(DEFAULT_MAX_HEALTH), m_Status(Status::ALIVE) {}
	Bible(uint16 health)	: m_Health(health), m_Status(Status::ALIVE) {}

	void	TakeDamage(uint16 damage)	{ if (damage >= m_Health) m_Status = Status::DEAD; else m_Health -= damage; }

	void	SetStatus(Status status)	{ m_Status = status; }
	Status	GetStatus() const			{ return m_Status; }

	uint16	GetHealth() const			{ return m_Health; }
private:
	uint16 m_Health;
	Status m_Status;

	static constexpr uint16 DEFAULT_MAX_HEALTH = 1000;
};