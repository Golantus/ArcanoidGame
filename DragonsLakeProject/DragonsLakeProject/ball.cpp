#include "ball.h"

int Ball::getDX() {
    return dX;
}

int Ball::getDY() {
    return dY;
}

void Ball::changeDX(){
    dX *= -1;
}

void Ball::changeDY() {
    dY *= -1;
}

bool Ball::getOnPlatform() {
    return onPlatform;
}

void Ball::launch(int dx, int dy) {
    onPlatform = false;
    dX = dx;
    dY = dy;
    move();
}

bool Ball::blocksCollision(Actor * block) {
	bool collided = false;
	if ( //collision detection
		block->getX() < getRigthBorder() &&
		block->getRigthBorder() > getX() &&
		block->getY() < getLowerBorder() && 
		block->getLowerBorder() > getY()
		) {
		int DELTA_X, DELTA_Y; //detecting direction to reflect the ball
		if (getDX() >= 0) 
			DELTA_X = getRigthBorder() - block->getX();
		else
			DELTA_X = block->getRigthBorder() - getX();
		if (getDY() <= 0)
			DELTA_Y = getLowerBorder() - block->getY();
		else
			DELTA_Y = block->getLowerBorder() - getY();
		if (DELTA_X > DELTA_Y) {
			if (getDY() > 0) {
				setY(block->getLowerBorder());
			}
			else {
				setY(block->getY() - getHeight());
			}
			changeDY();
			collided = true;
		}
		else if (DELTA_Y > DELTA_X) {
			if (getDX() > 0)
				setX(block->getX() - getWidth());
			else
				setX(block->getRigthBorder());
			changeDX();
			collided = true;
		}
	}
	return collided;
}

double Ball::getSpeed() {
    return speed;
}

void Ball::setSpeed(double speed) {
	this->speed = speed;
}

void Ball::changeSpeed(bool isPlatform) {
    if (isPlatform)
        speed *= 1.15;
    else
        speed *= 0.9;
    if (speed > initialSpeed * 3)
        speed = initialSpeed * 3;
    if (speed < initialSpeed * 0.4)
        speed = initialSpeed * 0.4;
}

void Ball::setBuffSpeed(bool min) {
	if (min)
		speed = initialSpeed * 0.4;
	else
		speed = initialSpeed * 3;
}

void Ball::move() {
    double relativeSpeed = (speed / sqrt((dX * dX) + (dY * dY)));
	//finding relative speed by pythagoras theoreme

	//temp coords is used to transform double coords into int coords
    temp_X_coords += relativeSpeed * dX;
    temp_Y_coords += relativeSpeed * dY;
    if (temp_X_coords >= 1.0 || temp_X_coords <= -1.0) {
        posX += int(temp_X_coords);
        temp_X_coords -= int(temp_X_coords);
    }
    if (temp_Y_coords >= 1.0 || temp_Y_coords <= 1.0) {
        posY -= int(temp_Y_coords);
        temp_Y_coords -= int(temp_Y_coords);
    }
}

Ball::Ball(int x, int y, int speed) : Actor(x, y) {
    onPlatform = true;
    this->speed = speed;
    initialSpeed = speed;
	initialX = x;
	initialY = y;
}

Ball::~Ball() {}
