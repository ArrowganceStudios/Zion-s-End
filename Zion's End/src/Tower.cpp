#include "Tower.h"
#include "LiteralTypes.h"
#include "Resources.h"
#include "Math.h"

constexpr uint16 canonTextureWidth = 95;
constexpr uint16 canonTextureHeight = 160;
constexpr uint16 towerTextureSize = 256;
constexpr float DEFAULT_COOLDOWN = 2.f;

Tower::Graphics::Graphics(sf::Texture* texture)
{
	m_pTexture = texture;

	m_TowerSprite.setTexture(*m_pTexture);
	m_TowerSprite.setTextureRect(sf::IntRect(0, 0, towerTextureSize, towerTextureSize));
	m_TowerSprite.setOrigin(towerTextureSize / 2, towerTextureSize / 2);

	m_CanonSprite.setTexture(*m_pTexture);
	m_CanonSprite.setTextureRect(sf::IntRect(towerTextureSize, 0, canonTextureWidth, canonTextureHeight));
	m_CanonSprite.setOrigin({ canonTextureWidth / 2.0f, (float)canonTextureHeight + 25.0f });

	//TODO:	to consult
	constexpr float randomScale = 0.33f;
	m_TowerSprite.setScale(randomScale, randomScale);
	m_CanonSprite.setScale(randomScale, randomScale);
}

void Tower::Graphics::WindowSizeUpdated(const uint16 windowWidth, const uint8 gridHeight)
{
	//TODO:	to consult
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

Tower::Tower(Graphics & graphics) : m_Graphics(graphics)
{
	m_Graphics = graphics;
	m_CanonCooldown = sf::seconds(DEFAULT_COOLDOWN);
	SetRotation((float)rand());	//	TODO: AUTO AIM
	SetAlive(false);
}

void Tower::Update(sf::Time deltaTime, Resources * resources)
{
	if (!IsAlive()) return;

	// TODO: target selection
	//float rotation = GetRotation();
	//rotation += deltaTime.asMilliseconds() / 2.0f;
	//SetRotation(rotation);

	m_CanonCooldown -= deltaTime;
	if (m_CanonCooldown < sf::seconds(0))
		Shoot(resources);
}

void Tower::Render(sf::RenderTarget & renderer)
{
	if (!IsAlive()) return;
	m_Graphics.Render(renderer, m_Position);
}

void Tower::Shoot(class Resources* resources)
{
	resources->GetProjectileManager()->SpawnProjectile(GetPosition(), as::Direction(GetRotation()));
	m_CanonCooldown = sf::seconds(DEFAULT_COOLDOWN);
}

void Tower::SetRotation(float angle)
{
	m_Rotation = angle;
	m_Graphics.SetCanonRotation(angle + 90);
}