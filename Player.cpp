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
	this->_player1.setPosition(200, 200);
	this->_player1.setOrigin(this->_player1.getRadius(), this->_player1.getRadius());
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
			int ChosenBound = _ObstacleBounds();
			std::cout << "Chosen Bound: " << ChosenBound << "\n";
			if (!this->_OutOfBounds_X(window) || !this->_OutOfBounds_Y(window)) // if it is out of bounds then go back to previous position
			{
				this->_player1.setPosition(currPos);
			}
		}
	}
	
}
int Player::_ObstacleBounds()
{
    float playerRadius = this->Diameter / 2.0f;

    sf::Vector2f playerPosition = this->_player1.getPosition();
	uint16_t  count = 1;
    for (const auto& obstacle : obstacles)
    {
        sf::Vector2f obstaclePosition = obstacle.getPosition();
        sf::Vector2f obstacleSize = obstacle.getSize();

        float closestX = std::clamp(playerPosition.x, obstaclePosition.x, obstaclePosition.x + obstacleSize.x);
        float closestY = std::clamp(playerPosition.y, obstaclePosition.y, obstaclePosition.y + obstacleSize.y);

        float distanceX = playerPosition.x - closestX;
        float distanceY = playerPosition.y - closestY;

        float distanceSquared  = (distanceX * distanceX) + (distanceY * distanceY);
        float radiusSquared = playerRadius * playerRadius;

		std::cout << "Distance Squared " << count << ": " << distanceSquared << "\n";
		count++;
        if (distanceSquared <= radiusSquared)
        {
            // Collision detected
            return 3;
        } // distance X and Y <= playerRadius might be a bug and its corresponding && (line of code)
        else if (distanceX <= playerRadius && (closestY == obstaclePosition.y || closestY == obstaclePosition.y + obstacleSize.y))
        {
            // Collision along the Y-axis
            return 2;
        }
        else if (distanceY <= playerRadius && (closestX == obstaclePosition.x || closestX == obstaclePosition.x + obstacleSize.x))
        {
            // Collision along the X-axis
            return 1;
        }
    }

    // No collision detected
    return 0;
}

const bool Player::_OutOfBounds_Y(sf::RenderWindow& window)
{
	if (this->_player1.getPosition().y + (this->_player1.getRadius() * 2) > window.getSize().y + this->Move_Speed  * 2
		|| this->_player1.getPosition().y  < this->_player1.getRadius())
	{
		return false;
	}
	return true;
}
const bool Player::_OutOfBounds_X(sf::RenderWindow& window)
{
	if (this->_player1.getPosition().x + (this->_player1.getRadius() * 2) > window.getSize().x + this->Move_Speed * 2
		|| this->_player1.getPosition().x < this->_player1.getRadius())
	{
		return false;
	}
	return true;
}
void Player::renderPlayer(sf::RenderWindow& window)
{
	window.draw(this->_player1);
}