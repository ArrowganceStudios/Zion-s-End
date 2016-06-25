#include "TowerManager.h"

void TowerManager::Init(Grid * targetGrid)
{
	m_pTargetGrid = targetGrid;
	m_TowerTexture.loadFromFile("assets/TowerSpriteSheet.png");

	Tower::Graphics towerGraphics(&m_TowerTexture);
	for (int i = 0; i < MAX_TOWERS; ++i)
	{
		m_TowerArray[i] = Tower(towerGraphics);
	}
}

void TowerManager::Update(sf::Time deltaTime)
{
	for (int i = 0; i < MAX_TOWERS; ++i)
		m_TowerArray[i].Update(deltaTime, m_pTargetGrid);
}

void TowerManager::Render(sf::RenderTarget &renderer)
{
	for (int i = 0; i < MAX_TOWERS; ++i)
		m_TowerArray[i].Render(renderer);
}

void TowerManager::SpawnTower(uint8 row, uint8 column)
{
	auto type = m_pTargetGrid->GetTypeOfTileAt(row, column);
	if (m_pTargetGrid->GetTypeOfTileAt(row, column) != Grid::Tile::Type::VACANT_TILE) return;

	for (int i = 0; i < MAX_TOWERS; ++i)
	{
		if (!m_TowerArray[i].IsAlive())
		{
			m_TowerArray[i].SetPosition(m_pTargetGrid->GetTileCenterAt(column, row));
			m_TowerArray[i].SetAlive(true);
			m_pTargetGrid->SetTypeOfTileAt(row, column, Grid::Tile::Type::OCCUPIED_TILE);
			break;
		}
	}
}