#pragma once
#include <String>
using namespace std;
using std::string;
#include <SFML/Graphics.hpp>


class paddle {
	int id;
	bool f_paddleWin;
	sf::Vector2f myPaddleSize;
public:
	sf::RectangleShape paddleShape;
	void paddleInit(sf::Vector2f paddlePos, sf::Vector2f paddleSize, int id_i);

	void paddleMoveUp(float deltaTime);
	void paddleMoveDown(float deltaTime);
	bool isBelowBoardTop(float deltaTime);
	bool isAboveBoardBottom(float deltaTime);

	float getPaddleTop();
	float getPaddleBottom();

	void paddlePowerupApply();
	void paddleSizeReset();
	sf::Vector2f getMyPaddleSize();
};
