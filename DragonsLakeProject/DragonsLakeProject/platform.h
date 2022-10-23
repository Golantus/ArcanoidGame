#include "actor.h"
#ifndef PLATFORM
#define PLATFORM

class Platform : public Actor {
private:
	int startX, startY;
public:
	void reset();
	void move(int dx);

	Platform(int x, int y);
	~Platform();
};

#endif
