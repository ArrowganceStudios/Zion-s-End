#pragma once
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include "LiteralTypes.h"
#include "Grid.h"

class Resources;

class Enemy
{
public:
	class Graphics
	{
	public:
		/**
		 * Default constructor, needs later assignment of a texture
		 */
		Graphics() = default;

		/**
		 * Constructs the graphics, and load the texture specified by the filePath provided in
		 * an argument
		 */
		Graphics(sf::Texture* texture);

		/**
		 * Sets the rotation of the sprite in (angle) degrees
		 */
		void SetRotation(float angle) { m_IdleSprite.setRotation(angle); }

		/**
		 * Renders the enemy based on the idle sprite and provided position
		 */
		void Render(sf::RenderTarget& renderer, const sf::Vector2f position);

	private:
		sf::Texture* m_pTexture;
		sf::Sprite	 m_IdleSprite;
	};

	enum class Mode
	{
		WALKING,
		ATTACKING
	};

public:
	/**
	 * Default construct
	 */
	Enemy() = default;

	/**
	 * Constructs the enemy, setting the graphics component, and position at starting tile
	 */
	Enemy(Graphics& graphicsComponent, Resources* resources);

	/**
	 * Called each gameloop iteration, performs AI operations
	 */
	void Update(sf::Time deltaTime, Resources* resources);

	/**
	 * Renders the enemy given a render target
  	*/
	void Render(sf::RenderTarget& renderer);

	/**
	 * Returns position
	 */
	const sf::Vector2f GetPosition() const { return m_Position; }

	/**
	 * Moves the enemy to the starting tile of given grid
	 */
	void ResetPosition(Grid* targetGrid);

	/**
	 * Damages the enemy for given value
	 */
	void Damage(uint16 damage);

	/**
	 * Sets the amount of health points
	 */
	void SetHealthPoints(int16 hp) { m_HealthPoints = hp; }
	
	/**
	 * Sets the state of the enemy
	 */
	void SetAlive(bool alive) { m_Alive = alive; }

	/**
	 * Checks if the enemy is alive
	 */
	bool IsAlive() const { return m_Alive; }

private:
	/**
	 * Choose new target based on neighbouring tiles
	 */
	Grid::Tile* Enemy::ChooseNewTileTarget(Grid* grid);

	/**
	 * Set new target
	 */
	void SetNewTarget(Grid* grid, Grid::Tile* tile);

	/**
	 *	Updates enemy when walking mode is set.
	 */
	void UpdateWalking(sf::Time deltaTime, Grid* grid);

	/**
	*	Updates enemy when attacking mode is set.
	*/
	void UpdateAttacking();

private:
	sf::Vector2f m_Position;
	sf::Vector2f m_Direction;
	sf::Vector2f m_Target;
	float		 m_Velocity;
	uint8		 m_CurrentTileIndex;
	uint8		 m_TargetTileIndex;
	int16		 m_HealthPoints;
	Mode		 m_Mode;
	bool		 m_Alive;
	Graphics	 m_Graphics;
};
