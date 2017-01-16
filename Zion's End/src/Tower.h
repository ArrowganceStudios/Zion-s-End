#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Grid.h"

class Resources;

class Tower
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
			Update sprites to match window size.
		*/
		void WindowSizeUpdated(const uint16 windowWidth, const uint8 gridHeight);

		/**
			Sets canon rotation in degrees
		*/
		void SetCanonRotation(float angle);

		/**
			Renders the tower
		*/
		void Render(sf::RenderTarget& renderer, sf::Vector2f position);

	private:
		sf::Texture* m_pTexture;
		sf::Sprite	 m_TowerSprite;
		sf::Sprite   m_CanonSprite;
	};

public:
	/**
		Default constructor with unitialized Graphics component
	*/
	Tower() = default;

	/**
		Sets the position, and initializes Graphics component	
	*/
	Tower(Graphics& graphics);

	/**
		Performs target selection, and shooting on demand
	*/
	void Update(sf::Time deltaTime, Resources* resources);

	/**
		Renders the tower
	*/
	void Render(sf::RenderTarget& renderer);

	/**
	 *	Shoots projectile
	 */
	void Shoot(Resources* resources);

	/**
		Sets new position
	*/
	void SetPosition(sf::Vector2f newPos) { m_Position = newPos; }

	/**
		Returns position
	*/
	sf::Vector2f GetPosition() const { return m_Position; }

	/**
		Sets rotation of the cannon
	*/
	void SetRotation(float angle);

	/**
		Gets rotation of the cannon
	*/
	float GetRotation() { return m_Rotation; }

	/**
		Sets the state of the tower
	*/
	void SetAlive(bool alive) { m_Alive = alive; }

	/**
		Checks if the tower is alive (placed on the field)
	*/
	bool IsAlive() const { return m_Alive; }

private:
	Graphics	 m_Graphics;
	sf::Vector2f m_Position;
	sf::Vector2f m_Target;
	sf::Time	 m_CanonCooldown;
	float		 m_Rotation;
	bool		 m_Alive;
};