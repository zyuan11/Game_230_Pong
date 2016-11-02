#pragma once
using namespace std;
#include <SFML/Graphics.hpp>
#include "paddle.h"

class paddle_AI : public paddle {
public:
	void paddleAIMove(float ballPos_y, float deltaTime);
	bool isBelowBall(float ballPos_y);
	bool isAboveBall(float ballPos_y);
	void AIMoveUp(float deltaTime);
	void AIMoveDown(float deltaTime);
};