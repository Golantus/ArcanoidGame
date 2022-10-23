#ifndef MYHEADER
#define MYHEADER

#include <iostream>
#include <string>
#include "Framework.h"
#include "actor.h"
#include "platform.h"
#include "brick.h"
#include "buff.h"
#include "ball.h"

#define BRICKS_COUNT 56
#define MAX_BALLS_COUNT 20


void screen_settings(int* width, int* height, bool* fullscreen, int argc, const char* argv[]);
int getRandomNumber(int min, int max);

enum buffList {
	DAMAGED,
	HEALTH,
	SIZEUP,
	SIZEDOWN,
	SPEEDUP,
	SPEEDDOWN,
	EXTRABALLS,
	COUNT
};

#endif