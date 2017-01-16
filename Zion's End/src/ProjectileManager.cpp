#include "ProjectileManager.h"

void ProjectileManager::Init()
{
	m_ProjectileTexture.loadFromFile("assets/projectile.png");

	Projectile::Graphics projectileGraphics(&m_ProjectileTexture);
	for (int i = 0; i < MAX_PROJECTILES; ++i)
	{
		m_ProjectileArray[i] = Projectile(projectileGraphics);
	}
}

void ProjectileManager::Update(sf::Time deltaTime)
{
	for (int i = 0; i < MAX_PROJECTILES; ++i)
		m_ProjectileArray[i].Update(deltaTime);
}

void ProjectileManager::Render(sf::RenderTarget& renderer)
{
	for (int i = 0; i < MAX_PROJECTILES; ++i)
		m_ProjectileArray[i].Render(renderer);
}

void ProjectileManager::SpawnProjectile(sf::Vector2f position, sf::Vector2f direction)
{
	for (int i = 0; i < MAX_PROJECTILES; ++i)
	{
		Projectile &cur = m_ProjectileArray[i];

		if (!cur.IsAlive())
		{
			cur.Spawn(position, direction);
			break;
		}
	}
}
