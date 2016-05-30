#pragma once
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include "LiteralTypes.h"
#include "Grid.h"

class Enemy
{
public:
	class Graphics
	{
	public:
		/**
			Default constructor, needs later assignment of a texture
		*/
		Graphics() = default;

		/**
			Constructs the graphics, and load the texture specified by the filePath provided in
			an argument
		*/
		Graphics(sf::Texture* texture);

		/**
			Sets the texture, and initializes the sprite
		*/
		void SetTexture(sf::Texture* texture);

		/**
			Rotates the sprite by (angle) degrees
		*/
		void Rotate(float angle) { m_IdleSprite.rotate(angle); }

		/**
			Sets the rotation of the sprite in (angle) degrees
		*/
		void SetRotation(float angle) { m_IdleSprite.setRotation(angle); }

		/**
			Renders the enemy based on the idle sprite and provided position
		*/
		void Render(sf::RenderTarget& renderer, const sf::Vector2f position);

	private:
		sf::Texture* m_pTexture;
		sf::Sprite	 m_IdleSprite;
	};

public:
	/**
		Default construct, needs later assignement of graphics component
		through SetGraphicsComponent(Graphics*) method.
	*/
	Enemy() = default;

	/**
		Creates invisible enemy, at pointed position (used for initial creation
		of enemy, where we spawn him somewhere far away from the map
	*/
	Enemy(sf::Vector2f position) : m_Position(position) {};

	/**
		Constructs the enemy, setting the graphics component, and velocity to 1.
	*/
	Enemy(Graphics& graphicsComponent) : m_Graphics(graphicsComponent), m_Velocity(1.0f) {}

	/**
		Constructs the enemy, setting the graphics component, and position at starting tile
	*/
	Enemy(Graphics& graphicsComponent, Grid* grid);

	/**
		Called each gameloop iteration, performs AI operations
	*/
	void Update(sf::Time deltaTime, Grid* grid);

	/**
		Returns position
	*/
	const sf::Vector2f GetPosition() const { return m_Position; }

	/**
		Renders the enemy given a render target
	*/
	void Render(sf::RenderTarget& renderer);

	/**
		Sets the graphics component of the enemy
	*/
	void SetGraphicsComponent(Graphics& graphicsComponent) { m_Graphics = graphicsComponent; }

private:
	/**
		Choose new target based on neighbouring tiles
	*/
	Grid::Tile* Enemy::ChooseNewTileTarget(Grid* grid);

	/**
		Set new target
	*/
	void SetNewTarget(Grid* grid, Grid::Tile* tile);

private:
	sf::Vector2f m_Position;
	sf::Vector2f m_Direction;
	sf::Vector2f m_Target;
	float		 m_Velocity;
	uint8		 m_CurrentTileIndex;
	uint8		 m_TargetTileIndex;
	uint8		 m_HealthPoints;
	Graphics	 m_Graphics;
};