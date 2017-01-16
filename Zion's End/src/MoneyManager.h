#pragma once
#include "LiteralTypes.h"

class MoneyManager
{
public:
	/**
	 * Creates money manager and sets initial money to 500.
	 */
	MoneyManager() : m_Money(500) {}

	/**
	 *	Adds money to current amount.
	 */
	void AddMoney(uint16 amount) { m_Money += amount; }
	
	/**
	 * Subtracts provided amount from current money count.
	 */
	void SubtractMoney(uint16 amount) { m_Money = amount > m_Money ? 0 : m_Money - amount; }

	/**
	 * Returns money.
	 */
	uint16 GetMoney() const { return m_Money; }
private:
	uint16 m_Money;
};