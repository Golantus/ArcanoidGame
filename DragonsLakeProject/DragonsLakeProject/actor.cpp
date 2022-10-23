#include "actor.h"

bool Actor::set_sprite(const char* path, int w, int h) {
	thisSprite = createSprite(path);
	if (!thisSprite)
		return false;
	else {
		setSpriteSize(thisSprite, w, h);
		width = w;
		heigth = h;
		initialWidth = width;
		initialHeight = heigth;
		return true;
	}
}

void Actor::get_sprite_size(int& w, int& h) {
	getSpriteSize(thisSprite, w, h);
}

void Actor::set_sprite_size(int w, int h) {
	width = w;
	heigth = h;
	setSpriteSize(thisSprite, width, heigth);
}

void Actor::draw_sprite() {
	drawSprite(thisSprite, posX, posY);
}

int Actor::getX() {
	return posX;
}

int Actor::getY() {
	return posY;
}

int Actor::getRigthBorder() {
	return posX+width;
}

int Actor::getLowerBorder() {
	return posY+heigth;
}

int Actor::getWidth() {
	return width;
}

int Actor::getHeight() {
	return heigth;
}

void Actor::changeX(int x) {
	posX += x;
}

void Actor::changeY(int y) {
	posY += y;
}

void Actor::setX(int x) {
	posX = x;
}

void Actor::setY(int y) {
	posY = y;
}

void Actor::changeSize(int deltaX, int deltaY) {
	width += deltaX;
	heigth += deltaY;
	set_sprite_size(width, heigth);
}

void Actor::resetSize() {
	width = initialWidth;
	heigth = initialHeight;
	set_sprite_size(width, heigth);
}


Actor::Actor(int x, int y) {
	posX = x;
	posY = y;
}

Actor::~Actor() {
	destroySprite(thisSprite);
}