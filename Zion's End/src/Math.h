#pragma once
#include <SFML\System.hpp>

/**
	Arrowgance Studios utilities
*/
namespace as
{
	/**
		Returns the dot product of vectors a and b.
	*/
	inline float Dot(sf::Vector2f a, sf::Vector2f b)
	{
		return a.x * b.x + a.y * b.y;
	}

	/**
		Returns the length of a vector
	*/
	inline float Length(sf::Vector2f vector)
	{
		return sqrtf(Dot(vector, vector));
	}

	/**
		Returns normalized vector
	*/
	inline sf::Vector2f Normalize(sf::Vector2f vector)
	{
		return vector / Length(vector);
	}

	/**
		Returns value in degrees, provided argument in radians
	*/
	inline float RadToDeg(float angle)
	{
		return angle * 57.2957795f;
	}

	/**
	 *	Returns value in radians, provided argument in degrees
	 */
	inline float DegToRad(float angle)
	{
		return angle / 57.2957795f;
	}

	/**
	Returns the direction from source to the destination
	*/
	inline sf::Vector2f Direction(sf::Vector2f source, sf::Vector2f destination)
	{
		return Normalize(destination - source);
	}

	/**
	Returns the direction based on angle (in radians)
	*/
	inline sf::Vector2f Direction(float angle)
	{
		float rad = DegToRad(angle);
		return sf::Vector2f(cosf(rad), sinf(rad));
	}
}