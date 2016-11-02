#include "block.h"
#include "main.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

void block::blockInit() {
	myBlock.setPosition(BLOCK_POSITION);
	myScale.x = myBlock.getGlobalBounds().width;
	myScale.y = myBlock.getGlobalBounds().height;
}