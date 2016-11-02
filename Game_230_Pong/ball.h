#pragma once
using namespace std;
#include "main.h"
#include <SFML/Graphics.hpp>

class ball {
public:
	sf::CircleShape ballShape;	
	float ballSpeed;
	float ballAngle;

	void ballInit(sf::Vector2f ballPos, float radius, sf::Color ballColor);
	void ballAngleInit();
	void ballSpeedUpdate();
	void ballSpeedReset();
	
	BALLSTATUS checkWin();
	
	bool collideWithTopBottomWall();
	void ballAngleUpdate_TBWall();

	bool collideWithLeftWall();
	bool collideWithRightWall();
	sf::Vector2f collideWithLeftPaddle(sf::Vector2f paddlePos, sf::Vector2f ballOrigin, sf::Vector2f paddleSize);
	sf::Vector2f collideWithRightPaddle(sf::Vector2f paddlePos, sf::Vector2f ballOrigin, sf::Vector2f paddleSize);
	void ballAngleUpdate_RPaddle(sf::Vector2f collisionPos, sf::Vector2f paddlePos_Curr, sf::Vector2f ballOrigin, sf::Vector2f paddleSize);
	void ballAngleUpdate_LPaddle(sf::Vector2f collisionPos, sf::Vector2f paddlePos_Curr, sf::Vector2f ballOrigin, sf::Vector2f paddleSize);
	
	void ballMove(float factor);

	bool detectPowerup(sf::Vector2f ballOrigin, sf::Vector2f powerupScale);
	bool collideWithBlock(sf::Vector2f ballOrigin, sf::Vector2f blockScale);
	void ballAngleUpdate_Block(sf::Vector2f ballOrigin, sf::Vector2f blockScale);
};