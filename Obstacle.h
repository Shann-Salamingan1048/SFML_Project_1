#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>

class Obstacle
{
protected:
	std::vector <sf::RectangleShape> obstacles;
private:
	sf::RectangleShape obstacle;
	sf::Vector2f obstacleSize;
	
	void initObstacle();
public:
	Obstacle();
	virtual ~Obstacle();
	void renderObstacle(sf::RenderWindow& window);
};