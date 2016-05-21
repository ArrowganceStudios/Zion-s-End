#include "Game.h"
#include "Math.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(sf::RenderWindow &r_TargetWindow)
{
	m_pResources = new Resources();
	m_pRenderTarget = &r_TargetWindow;
}

void Game::Update(sf::Time deltaTime)
{
	sf::Vector2f mousePos(sf::Mouse::getPosition(*m_pRenderTarget).x, sf::Mouse::getPosition(*m_pRenderTarget).y);
	auto p_Player = m_pResources->GetPlayer();
	auto p_Enemies = m_pResources->GetEnemyArray();

	sf::Vector2f directionToMouse = as::Direction(p_Player->getPosition(), mousePos);
	p_Player->move(directionToMouse * deltaTime.asSeconds() * m_pResources->GetPlayerVel());

	for (int i = 0; i < m_pResources->GetEnemyCount(); ++i)
	{
		sf::Vector2f directionToPlayer = as::Direction(p_Enemies[i].getPosition(), p_Player->getPosition());
		p_Enemies[i].move(directionToPlayer * deltaTime.asSeconds() * m_pResources->GetEnemyVel());
	}
}

void Game::Render()
{
	m_pRenderTarget->clear();

	//	render
	m_pRenderTarget->draw(*m_pResources->GetPlayer());
	for (int i = 0; i < m_pResources->GetEnemyCount(); ++i)
		m_pRenderTarget->draw(m_pResources->GetEnemyArray()[i]);
	//	endrender

	m_pRenderTarget->display();
}

void Game::Shutdown()
{
	delete m_pResources;
}

