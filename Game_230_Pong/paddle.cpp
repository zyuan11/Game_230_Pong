#include "paddle.h"
#include "main.h"
#include <iostream>
#include <String>
using namespace std;
using std::string;

void paddle::paddleInit(sf::Vector2f paddlePos, sf::Vector2f paddleSize, int id_i) {
	paddleShape.setSize(paddleSize);
	paddleShape.setPosition(paddlePos);
	paddleShape.setFillColor(PADDLE_COLOR);
	id = id_i;
	myPaddleSize = paddleSize;
}



void paddle::paddleMoveUp(float deltaTime) {
	if (isBelowBoardTop(deltaTime)) {
		paddleShape.move(0, -PADDLE_SPEED * deltaTime);
	}
}

void paddle::paddleMoveDown(float deltaTime) {
	if (isAboveBoardBottom(deltaTime)) {
		paddleShape.move(0, PADDLE_SPEED * deltaTime);
	}
}

bool paddle::isBelowBoardTop(float deltaTime) {
	sf::Vector2f paddlePos_curr = paddleShape.getPosition();
	if (paddlePos_curr.y - PADDLE_SPEED * deltaTime >= BOARD_TOP)
		return true;
	else
		return false;
}

bool paddle::isAboveBoardBottom(float deltaTime) {
	sf::Vector2f paddlePos_curr = paddleShape.getPosition();
	if (paddlePos_curr.y + PADDLE_SPEED * deltaTime <= BOARD_BOTTOM - myPaddleSize.y)
		return true;
	else
		return false;
}

float paddle::getPaddleTop() {
	return paddleShape.getPosition().y;
}

float paddle::getPaddleBottom() {
	return paddleShape.getPosition().y + myPaddleSize.y;
}

void paddle::paddlePowerupApply() {
	paddleShape.setSize(PADDLE_POWERUP_SIZE);
	myPaddleSize = PADDLE_POWERUP_SIZE;
}

void paddle::paddleSizeReset() {
	paddleShape.setSize(PADDLE_SIZE);
	myPaddleSize = PADDLE_SIZE;
}

sf::Vector2f paddle::getMyPaddleSize() {
	return myPaddleSize;
}