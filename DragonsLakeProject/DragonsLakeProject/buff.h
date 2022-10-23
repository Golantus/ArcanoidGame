#include "actor.h"
#ifndef BUFF
#define BUFF

class Buff : public Actor {
private:
	enum buffList buff;
	const int dy = 2;
	int scr_heigth;
public: 
	bool fallDown();
	bool checkCollision(Actor *platform);
	buffList getBuffType();

	Buff(int x, int y, buffList buff, int scr_heigth);
	~Buff();
};

#endif