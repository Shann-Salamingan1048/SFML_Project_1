#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Obstacle.h"
#include <cstdlib>
class Player : public Obstacle
{
private:
	sf::Vector2f PlayerMovement;
	sf::CircleShape _player1;
	
	void initPLayer();
	const bool _OutOfBounds_X(sf::RenderWindow& window);
	const bool _OutOfBounds_Y(sf::RenderWindow& window);
    int _ObstacleBounds();
	float Calculation_Axis(float val, float min, float max);
	float Diameter;
	float Move_Speed;
public:
	Player();
	~Player();
	void renderPlayer(sf::RenderWindow& window);
	void _ControllerPlayer(sf::RenderWindow& window, sf::Event& event);
};