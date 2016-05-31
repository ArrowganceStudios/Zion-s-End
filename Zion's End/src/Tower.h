#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Grid.h"

class Tower
{
public:
	class Graphics
	{
	public:
		/**
			Sets texture, and setups the sprites
		*/
		void SetTexture(sf::Texture* texture);

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
	Tower(Graphics& graphics, const sf::Vector2f position);

	/**
		Performs target selection, and shooting on demand
	*/
	void Update(sf::Time deltaTime, Grid* grid);

	/**
		Renders the tower
	*/
	void Render(sf::RenderTarget& renderer);

private:
	Graphics	 m_Graphics;
	sf::Vector2f m_Position;
	sf::Vector2f m_Target;
	sf::Time	 m_CanonCooldown;
};