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

				if (column > 0)
				{
					m_Neighbours[row][column].push_back(&m_Tiles[row - 1][column - 1]);
				}
				if (column < s_Width - 1)
				{
					m_Neighbours[row][column].push_back(&m_Tiles[row - 1][column + 1]);
				}
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

				if (column > 0)
				{
					m_Neighbours[row][column].push_back(&m_Tiles[row + 1][column - 1]);
				}

				if (column < s_Width - 1)
				{
					m_Neighbours[row][column].push_back(&m_Tiles[row + 1][column + 1]);
				}
			}
		}
	}

	// Texture settings
	m_TerrainTexture.loadFromFile("assets/Terrain.png");

	constexpr unsigned int textureSize = 256;
	constexpr float scale = (768.0f / (float)s_Height) / textureSize;
	m_GrassSprite.setTexture(m_TerrainTexture);
	m_GrassSprite.setTextureRect(sf::IntRect(0, 0, textureSize, textureSize));
	m_GrassSprite.setScale(scale, scale);
	m_RockSprite.setTexture(m_TerrainTexture);
	m_RockSprite.setTextureRect(sf::IntRect(textureSize, 0, textureSize, textureSize));
	m_RockSprite.setScale(scale, scale);
	m_BookSprite.setTexture(m_TerrainTexture);
	m_BookSprite.setTextureRect(sf::IntRect(textureSize * 2, 0, textureSize, textureSize));
	m_BookSprite.setScale(scale, scale);
}

const Grid::Tile Grid::GetTileAtPixel(float x, float y, uint16 windowWidth, uint16 windowHeight)
{
	if (x > 1.0f &&
		y > 1.0f &&
		x + 1.0f <= (float)windowWidth &&
		y + 1.0f <= (float)windowHeight)
	{
		return GetTileReferenceAtPixel(x, y, windowWidth, windowHeight);
	}
	else
	{
		return Tile();
	}
}

void Grid::SetTypeOfTileAtPixel(float x, float y, uint16 windowWidth, uint16 windowHeight, Tile::Type type)
{
	if (x > 1.0f &&
		y > 1.0f &&
		x + 1.0f <= (float)windowWidth &&
		y + 1.0f <= (float)windowHeight)
	{
		GetTileReferenceAtPixel(x, y, windowWidth, windowHeight).type = type;
	}
}

void Grid::Render(sf::RenderTarget& renderer)
{
	const float tileWidth = GetTileWidth(renderer.getSize().x);
	const float tileHeight = GetTileHeight(renderer.getSize().y);

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

Grid::Tile& Grid::GetTileReferenceAtPixel(float x, float y, uint16 windowWidth, uint16 windowHeight)
{
	float normalizedX = x / (float)windowWidth;
	float normalizedY = y / (float)windowHeight;

	uint8 tiledX = (uint8)(normalizedX * s_Width); // TODO: Check if it rounds/floors properly
	uint8 tiledY = (uint8)(normalizedY * s_Height);

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
