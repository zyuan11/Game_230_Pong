#include "ball.h"
#include "main.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

void ball::ballInit(sf::Vector2f ballPos, float radius, sf::Color ballColor) {
	ballShape.setPosition(ballPos);
	ballShape.setRadius(radius);
	ballShape.setFillColor(ballColor);
	
	ballAngleInit();
	ballSpeed = BALL_MIN_SPEED;
}

void ball::ballAngleInit() {
	srand(time(NULL));
	do
	{
		ballAngle = (rand() % CIRCLE_DEGREE * 2 * PI) / CIRCLE_DEGREE;
	} while (std::abs(std::cos(ballAngle)) < 0.7f);
}

void ball::ballSpeedUpdate() {
	if (ballSpeed < BALL_MAX_SPEED) {
		ballSpeed += 25;
	}
}

void ball::ballSpeedReset() {
	ballSpeed = BALL_MIN_SPEED;
}


BALLSTATUS ball::checkWin() {
	if (collideWithLeftWall())
		return  RightWin;
	else if (collideWithRightWall())
		return LeftWin;
	else
		return InProgress;
}

bool ball::collideWithTopBottomWall() {
	//ball collides with top wall ||
	//ball collides with bottom wall
	if (ballShape.getPosition().y <= 0 ||
		ballShape.getPosition().y + BALL_RADIUS *2 >= BOARD_HEIGHT)
		return true;
	else
		return false;
}

bool ball::collideWithLeftWall() {
	if (ballShape.getPosition().x <= 0)
		return true;
	else
		return false;
}

bool ball::collideWithRightWall() {
	if (ballShape.getPosition().x + BALL_RADIUS * 2 >= BOARD_WIDTH)
		return true;
	else
		return false;
}

sf::Vector2f ball::collideWithLeftPaddle(sf::Vector2f paddlePos, sf::Vector2f ballOrigin, sf::Vector2f paddleSize) {
	sf::Vector2f collisionPos  = NO_COLLISION_POSITION;
	//ball and paddle collide at right side of the paddle
	if (ballOrigin.x - BALL_RADIUS >= paddlePos.x &&
		ballOrigin.x - BALL_RADIUS <= paddlePos.x + paddleSize.x &&
		ballOrigin.y < paddlePos.y + paddleSize.y &&
		ballOrigin.y > paddlePos.y) {
		collisionPos.x = paddlePos.x + paddleSize.x;
		collisionPos.y = ballOrigin.y;
		cout << "ball and paddle collide at right side of the paddle" << endl;
	}
	//ball and paddle collide at top side of the paddle
	else if (ballOrigin.x - BALL_RADIUS <= paddlePos.x + paddleSize.x &&
		ballOrigin.x - BALL_RADIUS >= paddlePos.x - paddleSize.x &&
		ballOrigin.x <= paddlePos.y &&
		ballOrigin.y >= paddlePos.y - BALL_RADIUS) {
		collisionPos.x = paddlePos.x + paddleSize.x;
		collisionPos.y = paddlePos.y;
		cout << "ball and paddle collide at top side of the paddle" << endl;
	}
	//ball and paddle collide at bottom side of the paddle
	else if (ballOrigin.x - BALL_RADIUS <= paddlePos.x + paddleSize.x &&
		ballOrigin.x - BALL_RADIUS >= paddlePos.x - paddleSize.x &&
		ballOrigin.y >= paddlePos.y + paddleSize.y &&
		ballOrigin.y <= paddlePos.y + paddleSize.y + BALL_RADIUS) {
		collisionPos.x = paddlePos.x + paddleSize.x;
		collisionPos.y = paddlePos.y + paddleSize.y;
		cout << "ball and paddle collide at bottom side of the paddle" << endl;
	}
	return collisionPos;
}

sf::Vector2f ball::collideWithRightPaddle(sf::Vector2f paddlePos, sf::Vector2f ballOrigin, sf::Vector2f paddleSize) {
	sf::Vector2f collisionPos = NO_COLLISION_POSITION;

	//ball and paddle collide at left side of the paddle
	if (ballOrigin.x + BALL_RADIUS >= paddlePos.x &&
		ballOrigin.x + BALL_RADIUS <= paddlePos.x + paddleSize.x &&
		ballOrigin.y > paddlePos.y &&
		ballOrigin.y < paddlePos.y + paddleSize.y) {
		collisionPos.x = paddlePos.x;
		collisionPos.y = ballOrigin.y;
		cout << "ball and paddle collide at left side of the paddle" << endl;
	}
	//ball and paddle collide at top of the paddle
	else if (ballOrigin.x + BALL_RADIUS >= paddlePos.x &&
		ballOrigin.x + BALL_RADIUS <= paddlePos.x + paddleSize.x + BALL_RADIUS &&
		ballOrigin.y <= paddlePos.y &&
		ballOrigin.y >= paddlePos.y) {
		collisionPos = paddlePos;
		cout << "ball and paddle collide at top of the paddle" << endl;
	}
	//ball and paddle collide at bottom of the paddle
	else if (ballOrigin.x + BALL_RADIUS >= paddlePos.x &&
		ballOrigin.x + BALL_RADIUS <= paddlePos.x + paddleSize.x + BALL_RADIUS &&
		ballOrigin.y >= paddlePos.y + paddleSize.y &&
		ballOrigin.y <= paddlePos.y + paddleSize.y + BALL_RADIUS) {
		collisionPos.x = paddlePos.x;
		collisionPos.y = paddlePos.y + paddleSize.y;
		cout << "ball and paddle collide at bottom of the paddle" << endl;
	}
	return collisionPos;
}

//Update ball angle when collides with top or bottom wall
void ball::ballAngleUpdate_TBWall() {
	ballAngle = -ballAngle;
}

void ball::ballAngleUpdate_RPaddle(sf::Vector2f collisionPos, sf::Vector2f paddlePos_Curr, sf::Vector2f ballOrigin, sf::Vector2f paddleSize) {
	//ball and paddle collide at right side of the paddle
	if (collisionPos.x == paddlePos_Curr.x &&
		collisionPos.y == ballOrigin.y) {
		float paddleSize_HalfY = paddleSize.y / 2;
		float paddlePos_CenterY = paddlePos_Curr.y + paddleSize_HalfY;

		//ball and paddle collide at the center of the paddle
		if (collisionPos.y == paddlePos_CenterY) {
			ballAngle = PI;
			cout << "collide at the center" << endl;
		}
		
		//ball and paddle collides at either upper or lower part of the right side of the paddle
		else {
			//collision happens at upper part of the paddle
			if (collisionPos.y < paddlePos_CenterY) {
				ballAngle = PI + ((paddlePos_CenterY - collisionPos.y) / paddleSize_HalfY * MAX_DEGREE * 2 * PI) / CIRCLE_DEGREE;
				cout << "collision happens at upper part of the paddle" << endl;
			}
			//collision happens at lower part of the paddle 
			else {
				ballAngle = PI - ((collisionPos.y - paddlePos_CenterY) / paddleSize_HalfY * MAX_DEGREE * 2 * PI) / CIRCLE_DEGREE;
				cout << "collide not at the center" << endl;
			}
		}
	}
	
	//ball and paddle collide at the top side of the paddle
	else if (collisionPos.x == paddlePos_Curr.x + paddleSize.x &&
		collisionPos.y == paddlePos_Curr.y) {
		ballAngle = PI + (MAX_DEGREE * 2 * PI) / CIRCLE_DEGREE;
	}
	
	//ball and paddle collide at the bottom side of the paddle
	else if (collisionPos.x == paddlePos_Curr.x + paddleSize.x &&
		collisionPos.y == paddlePos_Curr.y + paddleSize.y) {
		ballAngle = PI - (MAX_DEGREE * 2 * PI) / CIRCLE_DEGREE;
	}
}

void ball::ballAngleUpdate_LPaddle(sf::Vector2f collisionPos, sf::Vector2f paddlePos_Curr, sf::Vector2f ballOrigin, sf::Vector2f paddleSize) {
	//ball and paddle collide at left side of the paddle
	if (collisionPos.x == paddlePos_Curr.x + paddleSize.x &&
		collisionPos.y == ballOrigin.y) {
		float paddleSize_HalfY = paddleSize.y / 2;
		float paddlePos_CenterY = paddlePos_Curr.y + paddleSize_HalfY;

		//ball and paddle collide at the center of the paddle
		if (collisionPos.y == paddlePos_CenterY) {
			ballAngle = 0; 
			cout << "collide at the center" << endl;
		}
		//other cases
		else {
			//collision happens at upper part of the paddle
			if (collisionPos.y < paddlePos_CenterY) {
				ballAngle = - ((paddlePos_CenterY - collisionPos.y) / paddleSize_HalfY * MAX_DEGREE * 2 * PI) / CIRCLE_DEGREE;
				cout << "collision happens at upper part of the paddle" << endl;
			}
			//collision happens at lower part of the paddle 
			else {
				ballAngle = ((collisionPos.y - paddlePos_CenterY) / paddleSize_HalfY * MAX_DEGREE * 2 * PI) / CIRCLE_DEGREE;
				cout << "collide not at the center" << endl;
			}	
		}
	}
		
	//ball and paddle collide at the top side of the paddle
	if (collisionPos == paddlePos_Curr) {
		ballAngle = - (MAX_DEGREE * 2 * PI) / CIRCLE_DEGREE;
	}

	//ball and paddle collide at the bottom side of the paddle
	else if (collisionPos.x == paddlePos_Curr.x &&
		collisionPos.y == paddlePos_Curr.y + paddleSize.y) {
		ballAngle = (MAX_DEGREE * 2 * PI) / CIRCLE_DEGREE;
	}
}

void ball::ballMove(float factor) {
	ballShape.move(cos(ballAngle) * factor, sin(ballAngle) * factor);
}

bool ball::detectPowerup(sf::Vector2f ballOrigin, sf::Vector2f powerupScale) {
	if (ballOrigin.x >= POWERUP_POSITION.x - BALL_RADIUS &&
		ballOrigin.x <= POWERUP_POSITION.x + powerupScale.x + BALL_RADIUS &&
		ballOrigin.y >= POWERUP_POSITION.y -BALL_RADIUS && 
		ballOrigin.y <= POWERUP_POSITION.y + powerupScale.y + BALL_RADIUS)
		return true;
	else
		return false;
}

bool ball::collideWithBlock(sf::Vector2f ballOrigin, sf::Vector2f blockScale) {
	if (ballOrigin.x >= BLOCK_POSITION.x - BALL_RADIUS &&
		ballOrigin.x <= BLOCK_POSITION.x + blockScale.x + BALL_RADIUS &&
		ballOrigin.y >= BLOCK_POSITION.y - BALL_RADIUS &&
		ballOrigin.y <= BLOCK_POSITION.y + blockScale.y + BALL_RADIUS)
		return true;
	else
		return false;
}

void ball::ballAngleUpdate_Block(sf::Vector2f ballOrigin, sf::Vector2f blockScale) {

	if (ballOrigin.y >= BLOCK_POSITION.y - BALL_RADIUS &&
		ballOrigin.y <= BLOCK_POSITION.y + blockScale.y + BALL_RADIUS &&
		((ballOrigin.x >= BLOCK_POSITION.x - BALL_RADIUS && 
			ballOrigin.x <= BLOCK_POSITION.x) ||
		(ballOrigin.x <= BLOCK_POSITION.x + blockScale.x + BALL_RADIUS &&
			ballOrigin.x >= BLOCK_POSITION.x + blockScale.x)))
		ballAngle = PI - ballAngle;
	else if (ballOrigin.x >= BLOCK_POSITION.x - BALL_RADIUS &&
		ballOrigin.x <= BLOCK_POSITION.x + blockScale.x + BALL_RADIUS &&
		((ballOrigin.y >= BLOCK_POSITION.y - BALL_RADIUS && 
			ballOrigin.y <= BLOCK_POSITION.y) ||
		(ballOrigin.y <= BLOCK_POSITION.y + blockScale.y + BALL_RADIUS &&
			ballOrigin.y >= BLOCK_POSITION.y + blockScale.y)))
		ballAngle = -ballAngle;
}




