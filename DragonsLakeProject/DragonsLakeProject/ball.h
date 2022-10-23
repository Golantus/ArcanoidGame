#include "actor.h"
#ifndef BALL
#define BALL

class Ball : public Actor {
private:
	int dX; //vector directions
	int dY;
	double temp_X_coords; //to convert it into int coords in move()
	double temp_Y_coords;
	double speed;
	double initialSpeed;
	int initialX;
	int initialY;
	bool onPlatform;
public:
	int getDX();
	int getDY();
	void changeDX();
	void changeDY();
	bool getOnPlatform();
	void launch(int dx, int dy);
	bool blocksCollision(Actor* block);
	double getSpeed();
	void setSpeed(double speed);
	void changeSpeed(bool isPlatform); //increase or decrease speed by reflection
	void setBuffSpeed(bool min);
	void move();

	Ball(int x, int y, int speed);
	~Ball();
};

#endif
