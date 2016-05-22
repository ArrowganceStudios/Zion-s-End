#include "Grid.h"

void Grid::Init()
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
}

const Grid::Tile Grid::GetTileAtPixel(float x, float y, uint16 windowWidth, uint16 windowHeight)
{
	return GetTileReferenceAtPixel(x, y, windowWidth, windowHeight);
}

void Grid::SetTypeOfTileAtPixel(float x, float y, uint16 windowWidth, uint16 windowHeight, Tile::Type type)
{
	GetTileReferenceAtPixel(x, y, windowWidth, windowHeight).type = type;
}

Grid::Tile& Grid::GetTileReferenceAtPixel(float x, float y, uint16 windowWidth, uint16 windowHeight)
{
	float normalizedX = x / (float)windowWidth;
	float normalizedY = y / (float)windowHeight;

	uint8 tiledX = (uint8)(normalizedX * s_Width); // TODO: Check if it rounds/floors properly
	uint8 tiledY = (uint8)(normalizedY * s_Height);

	return m_Tiles[tiledY][tiledX];
}
