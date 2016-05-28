#include "Enemy.h"
#include "Math.h"

Enemy::Graphics::Graphics(const char * fileName)
{
	m_Texture.loadFromFile(fileName);

	constexpr uint8 textureSize = 128;
	m_IdleSprite.setTexture(m_Texture);
	m_IdleSprite.setTextureRect(sf::IntRect(4 * textureSize, 5 * textureSize, textureSize, textureSize));
	m_IdleSprite.setOrigin(textureSize / 2, textureSize / 2);
	m_IdleSprite.setRotation(90.0f); // TEMP: until we introduce animations
}

void Enemy::Graphics::Render(sf::RenderTarget & renderer, const sf::Vector2f position)
{
	m_IdleSprite.setPosition(position);
	renderer.draw(m_IdleSprite);
}

Enemy::Enemy(Graphics * graphicsComponent, Grid * grid) : m_pGraphics(graphicsComponent)
														, m_CurrentTileIndex(grid->GetStartingTileIndex())
														, m_TargetTileIndex(grid->GetStartingTileIndex() + 1) //TEMP!
														, m_Velocity(200.0f)
{
	m_pGraphics = graphicsComponent;
	m_Position = grid->GetCenterOfTileIndexedBy(grid->GetStartingTileIndex());

	auto tile = ChooseNewTileTarget(grid);
	SetNewTarget(grid, tile);
}

void Enemy::Update(sf::Time deltaTime, Grid* grid)
{
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
	m_pGraphics->Render(renderer, m_Position);
	/* debug
	sf::CircleShape target(5.0f);
	target.setPosition(m_Target);
	renderer.draw(target); */
}

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

void Enemy::SetNewTarget(Grid * grid, Grid::Tile * tile)
{
	m_CurrentTileIndex = m_TargetTileIndex;
	m_TargetTileIndex = tile->index;
	m_Target = grid->GetCenterOfTileIndexedBy(tile->index);

	auto newDirection = as::Direction(m_Position, m_Target);
	float angle = copysignf(1, atan2f(m_Direction.x - newDirection.x, m_Direction.y - newDirection.y)) * as::RadToDeg(acosf(as::Dot(m_Direction, newDirection)));
	m_pGraphics->Rotate(angle);

	m_Direction = newDirection;
}
