#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(sf::RenderWindow &r_TargetWindow)
{
	mp_Resources = new Resources();
	mp_RenderTarget = &r_TargetWindow;
}

void Game::Update(sf::Time deltaTime)
{
	sf::Vector2f mousePos(sf::Mouse::getPosition(*mp_RenderTarget).x, sf::Mouse::getPosition(*mp_RenderTarget).y);
	auto p_Player = mp_Resources->GetPlayer();
	auto p_Enemies = mp_Resources->GetEnemyArray();

	sf::Vector2f directionToMouse = mousePos - p_Player->getPosition();
	float dirToMouseLength = sqrt(powf(directionToMouse.x, 2) + powf(directionToMouse.y, 2));
	directionToMouse /= dirToMouseLength;
	p_Player->move(directionToMouse * deltaTime.asSeconds() * mp_Resources->GetPlayerVel());

	for (int i = 0; i < mp_Resources->GetEnemyCount(); ++i)
	{
		sf::Vector2f directionToPlayer = p_Player->getPosition() - p_Enemies[i].getPosition();
		float dirToPlayerLength = sqrt(powf(directionToPlayer.x, 2) + powf(directionToPlayer.y, 2));
		directionToPlayer /= dirToPlayerLength;
		p_Enemies[i].move(directionToPlayer * deltaTime.asSeconds() * mp_Resources->GetEnemyVel());
	}
}

void Game::Render()
{
	mp_RenderTarget->clear();

	//	render
	mp_RenderTarget->draw(*mp_Resources->GetPlayer());
	for (int i = 0; i < mp_Resources->GetEnemyCount(); ++i)
		mp_RenderTarget->draw(mp_Resources->GetEnemyArray()[i]);
	//	endrender

	mp_RenderTarget->display();
}

void Game::Shutdown()
{
	delete mp_Resources;
}

