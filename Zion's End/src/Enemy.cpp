#include "Enemy.h"

Enemy::Graphics::Graphics(const char * fileName)
{
	m_Texture.loadFromFile(fileName);

	constexpr uint8 textureSize = 128;
	m_IdleSprite.setTexture(m_Texture);
	m_IdleSprite.setTextureRect(sf::IntRect(4 * textureSize, 5 * textureSize, textureSize, textureSize));
}

void Enemy::Graphics::Render(sf::RenderTarget & renderer, const sf::Vector2f position)
{
	m_IdleSprite.setPosition(position);
	renderer.draw(m_IdleSprite);
}

void Enemy::Update(sf::Time deltaTime)
{
	m_Position.x = 5.0f;
	m_Position.y = 50.0f;
}

void Enemy::Render(sf::RenderTarget& renderer)
{
	m_pGraphics->Render(renderer, m_Position);
}
