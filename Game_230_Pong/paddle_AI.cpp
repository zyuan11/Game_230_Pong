#include <SFML/Graphics.hpp>
#include "paddle.h"
#include "main.h"
#include "paddle_AI.h"

void paddle_AI::paddleAIMove(float ballPos_y, float deltaTime) {
	if (isBelowBall(ballPos_y))
		AIMoveUp(deltaTime);
	else if (isAboveBall(ballPos_y))
		AIMoveDown(deltaTime);
}

bool paddle_AI::isBelowBall(float ballPos_y) {
	if (ballPos_y < getPaddleTop() + PADDLE_AI_FACTOR)
		return true;
	else
		return false;
}

bool paddle_AI::isAboveBall(float ballPos_y) {
	if (ballPos_y > getPaddleBottom() - PADDLE_AI_FACTOR)
		return true;
	else
		return false;
}

void paddle_AI::AIMoveUp(float deltaTime) {
	if (isBelowBoardTop(deltaTime)) {
		paddleShape.move(0, -PADDLE_AI_SPEED * deltaTime);
	}
}
void paddle_AI::AIMoveDown(float deltaTime) {
	if (isAboveBoardBottom(deltaTime)) {
		paddleShape.move(0, PADDLE_AI_SPEED * deltaTime);
	}
}
