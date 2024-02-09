#include "Obstacle.h"
void Obstacle::initObstacle()
{
	this->obstacleSize.x = 100.0f;
	this->obstacleSize.y = 100.0f;
	this->obstacle.setSize(this->obstacleSize);
	this->obstacle.setFillColor(sf::Color::Red);
	// vector
	for (uint16_t i = 0; i < 3; i++)
		this->obstacles.push_back(obstacle);
	// position
	this->obstacles[0].setPosition(200, 200);
	this->obstacles[1].setPosition(300, 500);
	this->obstacles[2].setPosition(500, 200);
}
void Obstacle::renderObstacle(sf::RenderWindow& window)
{
	for(auto& i : obstacles)
	  window.draw(i);
}
Obstacle::Obstacle()
{
	this->initObstacle();
}
Obstacle :: ~Obstacle()
{
	std::cout << "Obstacle.h Destructor!\n";
	this->obstacles.clear();
}
