#include "Player.h"
Player :: Player()
{
	this->initPLayer();
}
Player :: ~Player() 
{
	std::cout << "Player.h Destructor!\n";
}
void Player::initPLayer()
{
	this->_player1.setRadius(50);
	this->_player1.setFillColor(sf::Color::Blue);
	this->_player1.setPosition(100, 100);
	this->PlayerMovement.x = 0.0f;
	this->PlayerMovement.y = 0.0f;
	this->Diameter = this->_player1.getRadius() * 2;
	this->Move_Speed = 20.0f;
}
void Player::_ControllerPlayer(sf::RenderWindow& window, sf::Event& event)
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			break;  // Exit the loop when the window is closed
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			sf::Vector2f currPos= this->_player1.getPosition();
			switch (event.key.code)
			{
				case sf::Keyboard::A:
					this->PlayerMovement.x = -(this->Move_Speed);
					this->PlayerMovement.y = 0.0f;
					break;
				case sf::Keyboard::D:
					this->PlayerMovement.x = this->Move_Speed;
					this->PlayerMovement.y = 0.0f;
					break;
				case sf::Keyboard::W:
					this->PlayerMovement.y = -(this->Move_Speed);
					this->PlayerMovement.x = 0.0f;
					break;
				case sf::Keyboard::S:
					this->PlayerMovement.y = this->Move_Speed;
					this->PlayerMovement.x = 0.0f;
					break;
			}
			this->_player1.move(this->PlayerMovement);
			if (!this->_ObstacleBounds())
			{
				this->_player1.setPosition(currPos);
			}
			if (!this->_OutOfBounds_X(window) || !this->_OutOfBounds_Y(window)) // if it is out of bounds then go back to previous position
			{
				this->_player1.setPosition(currPos);
			}
		}
	}
	//std::cout << "Window X: " << window.getSize().x << "\n" << "Window Y: " << window.getSize().y << "\n";
	 std::cout << "Position Player X: " << this->_player1.getPosition().x << "\t";
	 std::cout << "Position Player Y: " << this->_player1.getPosition().y << "\t";
	 std::cout << "Cal X Left: " << this->_player1.getPosition().x  << "\t";
	 std::cout << "Cal X Right: " << this->_player1.getPosition().x + this->Diameter << "\n";
}
const bool Player::_ObstacleBounds()
{
	
	for (auto& i : obstacles)
	{
		bool PlayerY_Top = this->_player1.getPosition().y + this->PlayerMovement.y  > i.getPosition().x + i.getSize().x; // Head or Top
		bool PlayerY_Bot = this->_player1.getPosition().y + this->PlayerMovement.y + this->Diameter < i.getPosition().x; // Foot or Bot
		if (this->PlayerMovement.x > 0.0f) // Left X - Axis
		{
			if (
				(this->_player1.getPosition().x + this->PlayerMovement.x + this->Diameter > i.getPosition().x)
				&&
				(PlayerY_Bot || PlayerY_Top)
				)
				return false;
		}
		else if(this->PlayerMovement.x < 0.0f) // Right X - Axis
		{
			if (
				(this->_player1.getPosition().x + this->PlayerMovement.x < i.getPosition().x + i.getSize().x)
				&&
				(PlayerY_Bot || PlayerY_Top)
				)
				return false;
		}
	}
	return true;
		
}
const bool Player::_OutOfBounds_Y(sf::RenderWindow& window)
{
	if (this->_player1.getPosition().y + (this->_player1.getRadius() * 2) > window.getSize().y
		|| this->_player1.getPosition().y + this->PlayerMovement.y < -(abs(this->PlayerMovement.y)))
	{
		return false;
	}
	return true;
}
const bool Player::_OutOfBounds_X(sf::RenderWindow& window)
{
	if (this->_player1.getPosition().x + (this->_player1.getRadius() * 2) > window.getSize().x
		|| this->_player1.getPosition().x + this->PlayerMovement.x < -(abs(this->PlayerMovement.x)))
	{
		return false;
	}
	return true;
}
void Player::renderPlayer(sf::RenderWindow& window)
{
	window.draw(this->_player1);
}