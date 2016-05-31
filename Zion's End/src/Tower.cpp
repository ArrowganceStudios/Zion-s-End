#include "Tower.h"
#include "LiteralTypes.h"

constexpr uint16 canonTextureWidth = 95;
constexpr uint16 canonTextureHeight = 160;
constexpr uint16 towerTextureSize = 256;

void Tower::Graphics::SetTexture(sf::Texture* texture)
{
	m_pTexture = texture;

	m_TowerSprite.setTexture(*m_pTexture);
	m_TowerSprite.setTextureRect(sf::IntRect(0, 0, towerTextureSize, towerTextureSize));
	m_TowerSprite.setOrigin(towerTextureSize / 2, towerTextureSize / 2);

	m_CanonSprite.setTexture(*m_pTexture);
	m_CanonSprite.setTextureRect(sf::IntRect(towerTextureSize, 0, canonTextureWidth, canonTextureHeight));
	m_CanonSprite.setOrigin({ canonTextureWidth / 2.0f, (float)canonTextureHeight + 25.0f});
}

void Tower::Graphics::WindowSizeUpdated(const uint16 windowWidth, const uint8 gridHeight)
{
	const float towerScale = (windowWidth / (float)gridHeight) / (float)towerTextureSize;
	m_TowerSprite.setScale(towerScale, towerScale);
	m_CanonSprite.setScale(towerScale, towerScale);
}

void Tower::Graphics::SetCanonRotation(float angle)
{
	m_CanonSprite.setRotation(angle);
}

void Tower::Graphics::Render(sf::RenderTarget& renderer, sf::Vector2f position)
{
	m_CanonSprite.setPosition(position);
	renderer.draw(m_CanonSprite);
	m_TowerSprite.setPosition(position);
	renderer.draw(m_TowerSprite);
}

Tower::Tower(Graphics & graphics, const sf::Vector2f position) : m_Graphics(graphics)
															   , m_Position(position)
{
}

void Tower::Update(sf::Time deltaTime, Grid * grid)
{
	// TODO: target selection, shooting
	static float rotation = 0.0f;
	rotation += deltaTime.asMilliseconds() / 16.0f;
	m_Graphics.SetCanonRotation(rotation);
}

void Tower::Render(sf::RenderTarget & renderer)
{
	m_Graphics.Render(renderer, m_Position);
}
