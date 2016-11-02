#include "score.h"
#include "main.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

void score::scoreInit(sf::Vector2f scoreTextPos) {
	myScore = 0;
	scoreTextInit(scoreTextPos);
}

void score::scoreTextInit(sf::Vector2f scoreTextPos) {
	if (!myFont.loadFromFile("arial.ttf")) {
		cout << "Can't find font file" << endl;
		return;
	}

	myScoreText.setString(to_string(myScore));
	myScoreText.setFont(myFont);
	myScoreText.setColor(TEXT_COLOR);
	myScoreText.setCharacterSize(SCORE_TEXT_SIZE);
	myScoreText.setPosition(scoreTextPos);
}

void score::scoreTextReset() {
	myScoreText.setString("");
}

void score::scoreUpdate() {
	myScore += 1;
	scoreTextUpdate();
}

void score::scoreReset() {
	myScore = 0;
	scoreTextUpdate();
}

bool score::Wins() {
	if (myScore >= SCORE_MAX)
		return true;
	else
		return false;
}

void score::scoreTextUpdate() {
	myScoreText.setString(to_string(myScore));
}