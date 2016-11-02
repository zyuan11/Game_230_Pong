#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cstdlib>

#include "paddle.h"
#include "paddle_AI.h"
#include "paddle_human.h"
#include "ball.h"
#include "score.h"
#include "powerup.h"
#include "block.h"
#include "main.h"

using namespace std;

sf::RenderWindow window(sf::VideoMode(BOARD_WIDTH, BOARD_HEIGHT), "PONG!");
paddle_AI paddleLeft;
paddle_human paddleRight;
score scoreRight;
score scoreLeft;
ball ballplay;
powerup powerupplay;
block blockplay;
sf::Text winMsg;
sf::Font myFont;
sf::Texture powerupTexture;
sf::Texture blockTexture;

sf::SoundBuffer winSoundBuffer;
sf::Sound winSound;

BALLSTATUS ballStatus_Curr;

bool isPlaying;

void SoundInit() {
	if (!winSoundBuffer.loadFromFile("win.wav"))
		return ;
	winSound = sf::Sound(winSoundBuffer);
	winSound.setVolume(50);
}

void winMsgInit() {
	if (!myFont.loadFromFile("arial.ttf")) {
		return;
	}
	winMsg.setString("");
	winMsg.setFont(myFont);
	winMsg.setColor(sf::Color::White);
	winMsg.setCharacterSize(WINMSG_SIZE);
	winMsg.setPosition(WINMSG_POSITION);
}

//paddles and ball  
void GameInit() {
	paddleLeft.paddleInit(PADDLE_LEFT_POSITION, PADDLE_SIZE, 1);
	paddleRight.paddleInit(PADDLE_RIGHT_POSITION, PADDLE_SIZE, 2);
	
	ballplay.ballInit(BALL_POSITION, BALL_RADIUS, BALL_COLOR);
	
	scoreLeft.scoreTextReset();
	scoreRight.scoreTextReset();
	scoreLeft.scoreInit(SCORE_TEXT_LEFT_POSITION);
	scoreRight.scoreInit(SCORE_TEXT_RIGHT_POSITION);
	
	powerupTexture.loadFromFile("powerup.png");
	powerupplay.myPowerUp = sf::Sprite(powerupTexture);
	powerupplay.powerupInit();

	blockTexture.loadFromFile("block.png");
	blockplay.myBlock = sf::Sprite(blockTexture);
	blockplay.blockInit();

	winMsgInit();

	SoundInit();

	isPlaying = true;

	ballStatus_Curr = InProgress;
}

void EndOrRestartGame() {
	
	winSound.play();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		GameInit();
	}
	else
		isPlaying = false;
}



void windowDraw() {
	
	window.draw(paddleLeft.paddleShape);
	window.draw(paddleRight.paddleShape);
	
	window.draw(scoreLeft.myScoreText);
	window.draw(scoreRight.myScoreText);
	
	window.draw(ballplay.ballShape);
	
	if (!powerupplay.powerupApplied())
		window.draw(powerupplay.myPowerUp);

	window.draw(blockplay.myBlock);
	
	window.draw(winMsg);
}

void newturnReset() {
	ballplay.ballInit(BALL_POSITION, BALL_RADIUS, BALL_COLOR);
	powerupplay.powerupNewturnReset();
}

void paddleSizeReset() { 
	paddleRight.paddleSizeReset();
	paddleLeft.paddleSizeReset();
}

void powerupApply(Paddle paddleToApply) {
	switch (paddleToApply) {
	case Left:
		paddleLeft.paddlePowerupApply();
		break;
	case Right:
		paddleRight.paddlePowerupApply();
		break;
	case INIT:
		break;
	default:
		break;
	}
}

int main()
{
	sf::Clock clock;
	
		
	//paddles, scores, and ball initlization
	GameInit();

	while (window.isOpen())
	{
		//Window initlization
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(BACK_COLOR);

		//check if any player wins the turn
		ballStatus_Curr = ballplay.checkWin();
		if (ballStatus_Curr != InProgress) {
			
			ballplay.ballSpeedReset();

			//update scores if any player wins the turn
			if (ballStatus_Curr == RightWin) {
				scoreRight.scoreUpdate();
				newturnReset();
				paddleSizeReset();
			}
			else if (ballStatus_Curr == LeftWin) {
				scoreLeft.scoreUpdate();
				newturnReset();
				paddleSizeReset();
			}
				

			//check if any player wins the game
			if (scoreLeft.Wins()) {
				winMsg.setString("Player 1 wins!\nPress SPACE to start a new game.");
				EndOrRestartGame();
			}
			else if (scoreRight.Wins()) {
				winMsg.setString("Player 2 wins!\nPress SPACE to start a new game.");
				EndOrRestartGame();
			}
			else {
				ballStatus_Curr = InProgress;
			}
		}

		//Gameplay
		windowDraw();
		

		if (isPlaying) {
			float deltaTime = clock.restart().asSeconds();
			sf::Vector2f ballPos = ballplay.ballShape.getPosition();

			
			//AI player movement
			paddleLeft.paddleAIMove(ballPos.y, deltaTime);

			//human player movement
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				paddleRight.paddleMoveUp(deltaTime);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				paddleRight.paddleMoveDown(deltaTime);
			}

			//ball operation
			float factor = ballplay.ballSpeed * deltaTime;
			sf::Vector2f ballPos_Curr = ballplay.ballShape.getPosition();
			sf::Vector2f ballOrigin;
			ballOrigin.x = ballPos_Curr.x + BALL_RADIUS;
			ballOrigin.y = ballPos_Curr.y + BALL_RADIUS;
			
			sf::Vector2f paddleLeftPos_Curr = paddleLeft.paddleShape.getPosition();
			sf::Vector2f paddleRightPos_Curr = paddleRight.paddleShape.getPosition();
			
			sf::Vector2f collisionPosRight;
			sf::Vector2f collisionPosLeft;

			//check if collects powerup
			if (ballplay.detectPowerup(ballOrigin, powerupplay.myScale) && !powerupplay.powerupApplied()) {
				powerupApply(powerupplay.lastPaddle);
				powerupplay.powerupApplyOn();
			}
			
			//check if ball collides with any wall, any paddle, or block
			if (ballplay.collideWithTopBottomWall())
				ballplay.ballAngleUpdate_TBWall();

			else if (ballplay.collideWithBlock(ballOrigin, blockplay.myScale))
				ballplay.ballAngleUpdate_Block(ballOrigin, blockplay.myScale);
			
			else {
				collisionPosLeft = ballplay.collideWithLeftPaddle(paddleLeftPos_Curr, ballOrigin, paddleLeft.getMyPaddleSize());
				collisionPosRight = ballplay.collideWithRightPaddle(paddleRightPos_Curr, ballOrigin, paddleRight.getMyPaddleSize());

				//update ball angle if collision happens with left paddle
				if (collisionPosLeft != NO_COLLISION_POSITION) {
					ballplay.ballAngleUpdate_LPaddle(collisionPosLeft, paddleLeftPos_Curr, ballOrigin, paddleLeft.getMyPaddleSize());
					ballplay.ballSpeedUpdate();
					powerupplay.lastPaddleUpdate(Left);
				}
				//update ball angle if collision happens with right paddle
				else if (collisionPosRight != NO_COLLISION_POSITION) {
					ballplay.ballAngleUpdate_RPaddle(collisionPosRight, paddleRightPos_Curr, ballOrigin, paddleRight.getMyPaddleSize());
					ballplay.ballSpeedUpdate();
					powerupplay.lastPaddleUpdate(Right);
				}
					
			}
			
			//move ball
			ballplay.ballMove(factor);
			
		}
		else {
			EndOrRestartGame();
		}
		window.display();

	}

	return 0;
}
