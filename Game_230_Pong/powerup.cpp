#include "powerup.h"
#include "main.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

void powerup::powerupInit() {
	myPowerUp.setPosition(POWERUP_POSITION);
	myScale.x = myPowerUp.getGlobalBounds().width;
	myScale.y = myPowerUp.getGlobalBounds().height;
	f_powerupApply = false;
	lastPaddle = INIT;
}

void powerup::lastPaddleUpdate(Paddle lastPaddle_i) {
	lastPaddle = lastPaddle_i;
}

void powerup::powerupNewturnReset() {
	f_powerupApply = false;
	lastPaddle = INIT;
}

void powerup::powerupApplyOn() {
	f_powerupApply = true;
}

bool powerup::powerupApplied() {
	return f_powerupApply;
}