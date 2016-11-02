#pragma once
using namespace std;
#include "main.h"
#include <SFML/Graphics.hpp>

class block {
public:
	sf::Sprite myBlock;
	sf::Vector2f myScale;

	void blockInit();
};