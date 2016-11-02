#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include <cstdlib>

//BOARD
const int BOARD_HEIGHT = 600;
const int BOARD_WIDTH = 800;
const int BOARD_TOP = 0;
const int BOARD_BOTTOM = 600;
const int BOARD_LEFT = 0;
const int BOARD_RIGHT = 800;

//GAMEPLAY
const enum BALLSTATUS { InProgress = 0, LeftWin = 1, RightWin = 2 };
const int WINMSG_SIZE = 40;
const sf::Vector2f WINMSG_POSITION(100, 250);

//PADDLE
const sf::Vector2f PADDLE_SIZE(15, 80);
const sf::Vector2f PADDLE_POWERUP_SIZE(15, 120);
const sf::Vector2f PADDLE_LEFT_POSITION(20, 260);
const sf::Vector2f PADDLE_RIGHT_POSITION(760, 260);
const float PADDLE_SPEED = 700;
const float PADDLE_AI_SPEED = 550;
const float PADDLE_AI_FACTOR = 10;

//BALL
const float BALL_RADIUS = 10;
const sf::Vector2f BALL_POSITION(390, 290);
const float BALL_MIN_SPEED = 200;
const float BALL_MAX_SPEED = 600;

//COLLISION & ANGLE
const sf::Vector2f NO_COLLISION_POSITION(-1, -1);
const int CIRCLE_DEGREE = 360;
const int MAX_DEGREE = 75;
const float PI = 3.14159265359;

//SCORE
const int SCORE_MAX = 5;
const int SCORE_TEXT_SIZE = 70;
const sf::Vector2f SCORE_TEXT_LEFT_POSITION(200.f, 15.f);
const sf::Vector2f SCORE_TEXT_RIGHT_POSITION(600.f, 15.f);


//COLOR 
const sf::Color BACK_COLOR = sf::Color(178, 144, 144, 255);
const sf::Color PADDLE_COLOR = sf::Color(255, 230, 231, 255);
const sf::Color TEXT_COLOR = sf::Color(255, 230, 231, 255);
const sf::Color BALL_COLOR = sf::Color(255, 230, 231, 255);

//POWERUP
const sf::Vector2f POWERUP_POSITION(370, 120);
const enum Paddle { INIT = 0, Left = 1, Right = 2 };

//BLOCK
const sf::Vector2f BLOCK_POSITION(370, 420);
