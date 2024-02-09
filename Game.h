#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Player.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event event;
	sf::VideoMode videoMode;
	Player player1;
	
	void initWindow();
public:
	Game();
	~Game();
	const bool isRunning() const;
	void pollEvents();

	void update();
	void render();
};