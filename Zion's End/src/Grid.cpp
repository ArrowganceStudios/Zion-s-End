#include "Grid.h"

Grid::Grid()
{
	// Welcome to the land of branch misprediction, enjoy your stay
	for (int row = 0; row < s_Height; ++row)
	{
		for (int column = 0; column < s_Width; ++column)
		{
			// Adding surrounding neighbours of tile {row, column} to the vector indicated by same coordinates.
			if (row > 0)
			{
				m_Neighbours[row][column].push_back(&m_Tiles[row - 1][column]);
			}

			if (column < s_Width - 1)
			{
				m_Neighbours[row][column].push_back(&m_Tiles[row][column + 1]);
			}

			if (column > 0)
			{
				m_Neighbours[row][column].push_back(&m_Tiles[row][column - 1]);
			}

			if (row < s_Height - 1)
			{
				m_Neighbours[row][column].push_back(&m_Tiles[row + 1][column]);
			}
		}
	}

	for (int i = 0; i < s_Height; ++i)
	{
		for (int j = 0; j < s_Width; ++j)
		{
			m_Tiles[i][j].index = i * s_Width + j;
		}
	}

	// Texture settings
	m_TerrainTexture.loadFromFile("assets/Terrain.png");

	constexpr unsigned int textureSize = 256;
	m_GrassSprite.setTexture(m_TerrainTexture);
	m_GrassSprite.setTextureRect(sf::IntRect(0, 0, textureSize, textureSize));
	m_RockSprite.setTexture(m_TerrainTexture);
	m_RockSprite.setTextureRect(sf::IntRect(textureSize, 0, textureSize, textureSize));
	m_BookSprite.setTexture(m_TerrainTexture);
	m_BookSprite.setTextureRect(sf::IntRect(textureSize * 2, 0, textureSize, textureSize));
}

void Grid::SetWindowSize(sf::Vector2u size)
{
	m_WindowSize = size;
	// Update sprite sizes
	constexpr unsigned int textureSize = 256;
	const float scale = (size.y /(float)s_Height) / textureSize;
	m_GrassSprite.setScale(scale, scale);
	m_RockSprite.setScale(scale, scale);
	m_BookSprite.setScale(scale, scale);
}

const Grid::Tile Grid::GetTileAtPixel(float x, float y)
{
	if (x > 1.0f &&
		y > 1.0f &&
		x + 1.0f <= (float)m_WindowSize.x &&
		y + 1.0f <= (float)m_WindowSize.y)
	{
		return GetTileReferenceAtPixel(x, y);
	}
	else
	{
		return Tile(); //It should throw here in a fact
	}
}

const sf::Vector2f Grid::GetCenterOfTileIndexedBy(uint8 tileIndex)
{
	sf::Vector2u tileCellPosition = GetTileRowColumnFromIndex(tileIndex);
	const uint8 column = tileCellPosition.x;
	const uint8 row =	 tileCellPosition.y;

	return GetTileCenterAt(column, row);
}

const sf::Vector2f Grid::GetTileCenterAt(uint8 column, uint8 row) const
{
	const float tileWidth = GetTileWidth();
	const float tileHeight = GetTileHeight();

	const float x = tileWidth * ((float)column + 0.5f);
	const float y = tileHeight * ((float)row + 0.5f);

	return { x, y };
}

void Grid::SetTypeOfTileAtPixel(float x, float y, Tile::Type type)
{
	if (x > 1.0f &&
		y > 1.0f &&
		x + 1.0f <= (float)m_WindowSize.x &&
		y + 1.0f <= (float)m_WindowSize.y)
	{
		GetTileReferenceAtPixel(x, y).type = type;
	}
}

const std::vector<Grid::Tile*> Grid::GetNeighboursOf(uint8 index)
{
	sf::Vector2u tileCellPosition = GetTileRowColumnFromIndex(index);
	const uint8 column = tileCellPosition.x;
	const uint8 row = tileCellPosition.y;

	return m_Neighbours[row][column];
}

#pragma warning(push)
#pragma warning(disable: 4715)
const uint8 Grid::GetStartingTileIndex() const
{

	for (int i = 0; i < s_Height; ++i)
	{
		for (int j = 0; j < s_Width; ++j)
		{
			if (m_Tiles[i][j].type == Grid::Tile::Type::START_TILE)
				return m_Tiles[i][j].index;
		}
	}
}
#pragma warning(pop)

void Grid::Render(sf::RenderTarget& renderer)
{
	const float tileWidth = GetTileWidth();
	const float tileHeight = GetTileHeight();

	for (unsigned int i = 0; i < s_Height; ++i)
	{
		for (unsigned int j = 0; j < s_Width; ++j)
		{
			sf::Sprite& sprite = GetSpriteFor(m_Tiles[i][j]);
			sf::Vector2f position = { tileWidth * j, tileHeight * i };
			sprite.setPosition(position);
			renderer.draw(sprite);
		}
	}
}

Grid::Tile& Grid::GetTileReferenceAtPixel(float x, float y)
{
	const float normalizedX = x / (float)m_WindowSize.x;
	const float normalizedY = y / (float)m_WindowSize.y;

	const uint8 tiledX = (uint8)(normalizedX * s_Width);
	const uint8 tiledY = (uint8)(normalizedY * s_Height);

	return m_Tiles[tiledY][tiledX];
}

sf::Sprite& Grid::GetSpriteFor(const Tile& tile)
{
	switch (tile.type)
	{
	case Grid::Tile::Type::START_TILE:
	case Grid::Tile::Type::ROAD_TILE:
		return m_GrassSprite;
		
	case Grid::Tile::Type::VACANT_TILE:
	case Grid::Tile::Type::OCCUPIED_TILE:
		return m_RockSprite;

	case Grid::Tile::Type::END_TILE:
		return m_BookSprite;
	default:	
		return m_GrassSprite;
		break;
	}
}

sf::Vector2u Grid::GetTileRowColumnFromIndex(uint8 index)
{
	const uint8 row	   = index / s_Width;
	const uint8 column = index % s_Width;

	return { column, row};
}
