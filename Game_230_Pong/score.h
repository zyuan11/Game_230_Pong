#pragma once
using namespace std;
#include "main.h"
#include <SFML/Graphics.hpp>

class score {
	int myScore;
public:
	sf::Text myScoreText;
	sf::Font myFont;

	void scoreInit(sf::Vector2f scoreTextPos);
	void scoreTextInit(sf::Vector2f scoreTextPos);
	void scoreReset();
	void scoreUpdate();
	void scoreTextReset();
	bool Wins();
	void scoreTextUpdate();
};