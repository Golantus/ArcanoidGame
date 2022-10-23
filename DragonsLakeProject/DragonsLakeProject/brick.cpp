#include "brick.h"

Brick::Brick(int x, int y, bool isRed) :Actor(x, y) {
	this->isRed = isRed;
	isDestroyed = false;
}
Brick::~Brick() {}

bool Brick::getDestroyed() {
	return isDestroyed;
}

void Brick::setDestroyed(bool destroyed) {
	isDestroyed = destroyed;
}


bool Brick::getIsRed() {
	return isRed;
}
