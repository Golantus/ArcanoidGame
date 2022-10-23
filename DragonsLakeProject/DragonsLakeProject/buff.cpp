#include "buff.h"

bool Buff::fallDown(){
	posY += 1;
	if (posY > scr_heigth) {
		return 0;
	}
	return 1;
}

bool Buff::checkCollision(Actor *platform) {
	if (
		(platform)->getX() < getRigthBorder() &&
		(platform)->getRigthBorder() > getX() &&
		(platform)->getY() < getLowerBorder() &&
		(platform)->getLowerBorder() > getY()
		) {
		return 1;
	}
	return 0;
}

buffList Buff::getBuffType() {
	return buff;
}

Buff::Buff(int x, int y, buffList buff, int scr_heigth) : Actor(x, y) {
	this->buff = buff;
	this->scr_heigth = scr_heigth;
}

Buff::~Buff(){}
