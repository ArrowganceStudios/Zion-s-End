#include "Projectile.h"
#include "Math.h"

Projectile::Graphics::Graphics(sf::Texture* texture)
{
	m_pTexture = texture;
	uint8 textureSize = texture->getSize().x;
	m_Sprite.setTexture(*m_pTexture);
	m_Sprite.setOrigin((float)(textureSize / 2), (float)(textureSize / 2));

	//TODO:	to consult
	constexpr float randomScale = 0.33f;
	m_Sprite.setScale(randomScale, randomScale);
}

void Projectile::Graphics::Render(sf::RenderTarget& renderer, const sf::Vector2f position)
{
	m_Sprite.setPosition(position);
	renderer.draw(m_Sprite);
}

Projectile::Projectile(Graphics& graphicsComponent)
{
	m_Graphics = graphicsComponent;
	m_Velocity = DEFAULT_VELOCITY;
	m_Range = DEFAULT_RANGE;
	m_Damage = DEFAULT_DAMAGE;

	Collide(false);
	SetAlive(false);
}

void Projectile::Update(sf::Time deltaTime)
{
	if (!IsAlive()) return;
	if (HasCollided() || m_Range < 0)
	{
		SetAlive(false);
		return;
	}
	float increment = m_Velocity * deltaTime.asSeconds();
	m_Range -= increment;
	m_Position += m_Direction * increment;
}

void Projectile::Render(sf::RenderTarget& renderer)
{
	if (!IsAlive()) return;
	m_Graphics.Render(renderer, m_Position);
}

void Projectile::Spawn(sf::Vector2f initialPos, sf::Vector2f direction)
{
	m_Position = initialPos;
	m_Direction = as::Normalize(direction);
	m_Range = DEFAULT_RANGE;
	Collide(false);
	SetAlive(true);
}
