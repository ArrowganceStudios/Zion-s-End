#pragma once
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include "LiteralTypes.h"

class Enemy
{
public:
	class Graphics
	{
	public:
		/**
			Constructs the graphics, and load the texture specified by the filePath provided in
			an argument
		*/
		Graphics(const char* fileName);

		/**
			Renders the enemy based on the idle sprite and provided position
		*/
		void Render(sf::RenderTarget& renderer, const sf::Vector2f position);

	private:
		sf::Texture  m_Texture;
		sf::Sprite	 m_IdleSprite;
	};

public:
	/**
		Default construct, needs later assignement of graphics component
		through SetGraphicsComponent(Graphics*) method.
	*/
	Enemy() = default;
	
	/**
		Constructs the enemy, setting the graphics component
	*/
	Enemy(Graphics* graphicsComponent) : m_pGraphics(graphicsComponent) {}

	/**
		Called each gameloop iteration, performs AI operations
	*/
	void Update(sf::Time deltaTime);

	/**
		Renders the enemy given a render target
	*/
	void Render(sf::RenderTarget& renderer);

	/**
		Sets the graphics component of the enemy
	*/
	void SetGraphicsComponent(Graphics* graphicsComponent) { m_pGraphics = graphicsComponent; }

private:
	sf::Vector2f m_Position;
	sf::Vector2f m_Direction;
	float		 m_Velocity;
	uint8		 m_PreviousTileIndex;
	uint8		 m_CurrentTileIndex;
	uint8		 m_TargetTileIndex;
	uint8		 m_HealthPoints;
	Graphics*	 m_pGraphics;
};