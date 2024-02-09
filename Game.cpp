#include "Game.h"
void Game::initWindow()
{
	this->videoMode.height = 1000;
	this->videoMode.width = 1000;
	this->window = new sf::RenderWindow(this->videoMode, "Simple Game SFML", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
	
}
Game::Game()
{
	this->initWindow();
	
}
Game::~Game() // destructor
{
	std::cout << "Game.h Destructor!\n";
	delete this->window;
}
const bool Game::isRunning() const
{
	return this->window->isOpen();
}
void Game::pollEvents()
{
	this->player1._ControllerPlayer(*this->window, this->event);
}
void Game::update()
{
	this->pollEvents();
}
void Game::render()
{
	this->window->clear();
	this->player1.renderPlayer(*this->window);
	this->player1.renderObstacle(*this->window);
	this->window->display();
}