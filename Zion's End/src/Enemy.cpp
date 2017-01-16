#include "Enemy.h"
#include "Math.h"
#include "Tower.h"
#include "Resources.h"

Enemy::Graphics::Graphics(sf::Texture* texture)
{
	m_pTexture = texture;

	constexpr uint8 textureSize = 128;
	m_IdleSprite.setTexture(*m_pTexture);
	m_IdleSprite.setTextureRect(sf::IntRect(4 * textureSize, 5 * textureSize, textureSize, textureSize));
	m_IdleSprite.setOrigin(textureSize / 2, textureSize / 2);
}

void Enemy::Graphics::Render(sf::RenderTarget & renderer, const sf::Vector2f position)
{
	m_IdleSprite.setPosition(position);
	renderer.draw(m_IdleSprite);
}

Enemy::Enemy(Graphics& graphicsComponent, Grid * grid)
													 
{
	m_Graphics = graphicsComponent;
	m_Velocity = 100.0f;

	ResetPosition(grid);
	SetAlive(false);
}

void Enemy::Update(sf::Time deltaTime, Grid* grid)
{
	if (!IsAlive()) return;

	m_Position += m_Direction * m_Velocity * deltaTime.asSeconds();

	constexpr float MIN_DISTANCE_FOR_SWITCH = 85.0f / 2.0f;
	if (as::Length(m_Target - m_Position) < MIN_DISTANCE_FOR_SWITCH)
	{
		auto tile = ChooseNewTileTarget(grid);
		if (tile == nullptr)
		{ // TODO change this so the state is switched to "Attacking" instead of "walking"
			m_Direction = { 0.0f, 0.0f };
			return;
		}
		SetNewTarget(grid, tile);
	}
}

void Enemy::Render(sf::RenderTarget& renderer)
{
	if (!IsAlive()) return;
	m_Graphics.Render(renderer, m_Position);
}

void Enemy::ResetPosition(Grid * targetGrid)
{
	m_CurrentTileIndex = targetGrid->GetStartingTileIndex();
	m_Position = targetGrid->GetCenterOfTileIndexedBy(targetGrid->GetStartingTileIndex());
	m_TargetTileIndex = m_CurrentTileIndex;
	m_Target = m_Position;
}

void Enemy::Damage(uint16 damage, Resources* resources)
{
	if (!IsAlive()) return;
	m_HealthPoints -= damage;
	if (m_HealthPoints < 0)
		Die(resources);
}

#pragma warning(push)
#pragma warning(disable: 4715)
Grid::Tile* Enemy::ChooseNewTileTarget(Grid * grid)
{
	std::vector<Grid::Tile*> neighbours = grid->GetNeighboursOf(m_TargetTileIndex);

	for (unsigned int i = 0; neighbours.size(); ++i)
	{
		if (neighbours[i]->type == Grid::Tile::Type::ROAD_TILE &&
			neighbours[i]->index != m_CurrentTileIndex)
		{
			return neighbours[i];
		}
		else if (neighbours[i]->type == Grid::Tile::Type::END_TILE)
		{
			return nullptr;
		}
	}
}
#pragma warning(pop)

void Enemy::SetNewTarget(Grid * grid, Grid::Tile * tile)
{
	m_CurrentTileIndex = m_TargetTileIndex;
	m_TargetTileIndex = tile->index;
	m_Target = grid->GetCenterOfTileIndexedBy(tile->index);

	m_Direction = as::Direction(m_Position, m_Target);
	float angle = as::RadToDeg(atan2(m_Direction.y, m_Direction.x));
	m_Graphics.SetRotation(angle);
}

void Enemy::Die(Resources* resources)
{
	m_Alive = false;
	resources->GetMoneyManager()->AddMoney(100);
}
