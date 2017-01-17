#pragma once
#include "Projectile.h"

constexpr unsigned int MAX_PROJECTILES = 32;

class ProjectileManager
{
public:
	void Init();

	void Update(sf::Time deltaTime);
	void Render(sf::RenderTarget &renderer);

	void SpawnProjectile(sf::Vector2f position, sf::Vector2f direction);

	Projectile& operator[](unsigned int index) { return m_ProjectileArray[index % MAX_PROJECTILES]; }

private:

	Projectile m_ProjectileArray[MAX_PROJECTILES];

	sf::Texture m_ProjectileTexture;
};