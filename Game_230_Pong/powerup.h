#pragma once
using namespace std;
#include "main.h"
#include <SFML/Graphics.hpp>


class powerup {
public:
	sf::Sprite myPowerUp;
	sf::Vector2f myScale;
	Paddle lastPaddle;
	bool f_powerupApply;

	void powerupInit();
	void lastPaddleUpdate(Paddle lastPaddle_i);
	void powerupNewturnReset();
	void powerupApplyOn();
	bool powerupApplied();
};