#pragma once
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include "LiteralTypes.h"

constexpr float DEFAULT_VELOCITY = 250.f;
constexpr float DEFAULT_RANGE = 250.f;
constexpr uint16 DEFAULT_DAMAGE = 100;

class Projectile
{
public:
	class Graphics
	{
	public:
		/**
		 *	Default constructor, needs later assignment of a texture
		 */
		Graphics() = default;

		/**
		 *	Constructs the graphics, and load the texture specified by the pointer provided in
		 *	an argument
		 */
		Graphics(sf::Texture* texture);

		/**
		 *  Sets rotation of sprite in degrees
		 */
		void SetRotation(float angle) { m_Sprite.setRotation(angle); }

		/**
		 *  Renders the projectile
		 */
		void Render(sf::RenderTarget& renderer, const sf::Vector2f position);

	private:
		sf::Texture* m_pTexture;
		sf::Sprite m_Sprite;
	};

	/**
	 *	Default construct
	 */
	Projectile() = default;

	/**
	 *	Constructs the projectile, setting the graphics component
	 */
	Projectile(Graphics& graphicsComponent);

	/**
	 *  Called each gameloop iteration, updates the projectile
	 */
	void Update(sf::Time deltaTime);

	/**
	 *  Renders the projectile given a render target
	 */
	void Render(sf::RenderTarget& renderer);

	/**
	 *	Returns position
	 */
	sf::Vector2f GetPosition() const { return m_Position; }

	/**
	 *	Returns damage
	 */
	uint16 GetDamage() const { return m_Damage; }

	/**
	 *  Spawns projectile at given position with given direction
	 */
	void Spawn(sf::Vector2f initialPos, sf::Vector2f direction);

	/**
	 *  Sets the collided state to the projectile
	 */
	void Collide(bool col = true) { m_Collided = col; }

	/**
	 *	Checks if the projectile has collided
	 */
	bool HasCollided() const { return m_Collided; }

	/**
	 *	Sets the state of projectile
	 */
	void SetAlive(bool alive) { m_Alive = alive; }

	/**
	 * Checks if the projectile is alive
	 */
	bool IsAlive() const { return m_Alive; }

private:
	sf::Vector2f m_Position;
	sf::Vector2f m_Direction;
	float m_Velocity;
	float m_Range;
	uint16 m_Damage;
	bool m_Alive;
	bool m_Collided;
	Graphics m_Graphics;
};