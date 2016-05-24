#pragma once
#include <vector>
#include <SFML\Graphics.hpp>

#include "LiteralTypes.h"

class Grid
{
public:

	/**
		Structure representing a single tile on the map
	*/
	struct Tile
	{
	public:

		enum class Type
		{
			INVALID_TILE,
			START_TILE,
			END_TILE,
			ROAD_TILE,
			VACANT_TILE,
			OCCUPIED_TILE
		};

		Tile() : type(Type::INVALID_TILE) {}

		Tile(Type type) : type(type) {}

	public:
		Type type;
		// std::vector<GameObject> occupants;
	};

public:
	/**
		Generates the map of neighbours for each tile, loads the texture file, and sets up the sprites
	*/
	Grid();

	/**
		Returns the tile located at {row, column}
	*/
	const Tile GetTileAt(uint8 column, uint8 row) const { return m_Tiles[row][column]; }

	/**
		Returns tile located at pixel {x, y}
	*/
	const Tile GetTileAtPixel(float x, float y, uint16 windowWidth, uint16 windowHeight);

	/**
		Returns the width of the tile in pixels
	*/
	const float GetTileWidth(uint16 windowWidth) const { return windowWidth / (float)s_Width; }

	/**
		Returns the height of the tile in pixels
	*/
	const float GetTileHeight(uint16 windowHeight) const { return windowHeight / (float)s_Height; }

	/**
		Returns the width of the grid in tiles
	*/
	const uint8 GetGridWidth() const { return s_Width; }

	/**
		Returns the height of the grid in tiles
	*/
	const uint8 GetGridHeight() const { return s_Height; }

	/**
		Sets type of a tile indicated by it's tile coordinates
	*/
	void SetTypeOfTileAt(uint8 row, uint8 column, Tile::Type type) { m_Tiles[row][column].type = type; }

	/**
		Sets type of a tile indicated by it's pixel coordinates
	*/
	void SetTypeOfTileAtPixel(float x, float y, uint16 windowWidth, uint16 windowHeight, Tile::Type type);

	/**
		Returns vector of tiles that are neighbour of tile positioned at {row, column}
	*/
	const std::vector<Tile*> GetNeighboursOf(uint8 column, uint8 row) { return m_Neighbours[row][column]; }

	/**
		Renders the grid
	*/
	void Render(sf::RenderTarget& renderer);

private:
	/**
		Returns reference to the tile at specified pixel position {x, y}
	*/
	Tile& GetTileReferenceAtPixel(float x, float y, uint16 windowWidth, uint16 windowHeight);

	/**
		Returns a sprite corresponding to passed tile
	*/
	sf::Sprite& Grid::GetSpriteFor(const Tile& tile);

private:
	static constexpr uint8 s_Width = 12;
	static constexpr uint8 s_Height = 9;
	Tile				   m_Tiles[s_Height][s_Width];	   // Row-major
	std::vector<Tile*>	   m_Neighbours[s_Height][s_Width];
	sf::Texture			   m_TerrainTexture;
	sf::Sprite			   m_RockSprite;
	sf::Sprite			   m_GrassSprite;
	sf::Sprite			   m_BookSprite;
};