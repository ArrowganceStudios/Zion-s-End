#include "TowerManager.h"
#include "Resources.h"

void TowerManager::Init(Resources * targetResources)
{
	m_pResources = targetResources;
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
		m_TowerArray[i].Update(deltaTime, m_pResources);
}

void TowerManager::Render(sf::RenderTarget &renderer)
{
	for (int i = 0; i < MAX_TOWERS; ++i)
		m_TowerArray[i].Render(renderer);
}

void TowerManager::SpawnTower(uint8 row, uint8 column)
{
	auto type = m_pResources->GetGrid()->GetTypeOfTileAt(row, column);
	if (m_pResources->GetGrid()->GetTypeOfTileAt(row, column) != Grid::Tile::Type::VACANT_TILE) return;

	for (int i = 0; i < MAX_TOWERS; ++i)
	{
		if (!m_TowerArray[i].IsAlive())
		{
			m_TowerArray[i].SetPosition(m_pResources->GetGrid()->GetTileCenterAt(column, row));
			m_TowerArray[i].SetAlive(true);
			m_pResources->GetGrid()->SetTypeOfTileAt(row, column, Grid::Tile::Type::OCCUPIED_TILE);
			break;
		}
	}
}