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
float Player::Calculation_Axis(float playerPos, float min, float max)
{
	// calculate to collide
	if (playerPos < min) return min; // if the player position Position less than min then return min top outer
	else if (playerPos > max) return max; // if the player position Position greater than max then return max or the lower outer
	else return playerPos; // return playerPos if it is inside of the obstacle body
}
int Player::_ObstacleBounds()
{
	float Player_X_Min = this->_player1.getPosition().x;
	float Player_X_Max = this->_player1.getPosition().x + this->Diameter;
	float Player_Y_Min = this->_player1.getPosition().y;
	float Player_Y_Max = this->_player1.getPosition().y + this->Diameter;

	uint16_t count = 1; // count
	for (auto& i : obstacles)
	{
		// X
		float Obstacle_X_Min = i.getPosition().x;
		float Obstacle_X_Max = i.getPosition().x + i.getSize().x;
		// Y
		float Obstacle_Y_Min = i.getPosition().y;
		float Obstacle_Y_Max = i.getPosition().y + i.getSize().y;
		// Y
		float Player_Y_Closeest_Obs = Calculation_Axis(Player_Y_Min, Obstacle_Y_Min, Obstacle_Y_Max);
		float Distance_Y = Player_Y_Closeest_Obs - Player_Y_Min;
		//float Distance_Y = Player_Y_Min -  Player_Y_Closeest_Obs ;

		// X
		float Player_X_Closeest_Obs = Calculation_Axis(Player_X_Min, Obstacle_X_Min, Obstacle_X_Max);
		float Distance_X = Player_X_Closeest_Obs - Player_X_Min;
		//float Distance_X = Player_X_Min - Player_X_Closeest_Obs;

		// if the distance is less than the circle radius then collide
		float Distance = std::sqrt((Distance_X * Distance_X) + (Distance_Y * Distance_Y)); // corner
		
		
		//std::cout << "Distance " << count << ": " <<  Distance << "\n";
		std::cout << "Distance X" << count << ": " << Distance_X << "\t" << "Distance Y" << count << ": " << Distance_Y << "\n";
		count++;
		if (Distance < this->Diameter && Player_X_Closeest_Obs != Player_X_Min &&
			Player_Y_Closeest_Obs != Player_Y_Min)
		{
			return 3;
		}
		else if (Distance <= this->Diameter && Player_X_Closeest_Obs == Player_X_Min) // X 
		{
			return 2;
		}
		else if (Distance <= this->Diameter && Player_Y_Closeest_Obs == Player_Y_Min) // Y
		{
			return 1;
		}
	}
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