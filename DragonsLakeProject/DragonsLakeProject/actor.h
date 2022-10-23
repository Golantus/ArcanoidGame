#include "header.h"
#ifndef ACTOR
#define ACTOR

class Actor {
protected:
	Sprite *thisSprite;
	int posX, posY;
	int width, heigth;
	int initialWidth, initialHeight;
public:
	bool set_sprite(const char* path, int w, int h);
	void get_sprite_size(int& w, int& h);
	void set_sprite_size(int w, int h);
	void draw_sprite();
	int getX();
	int getY();
	int getRigthBorder();
	int getLowerBorder();
	int getWidth();
	int getHeight();
	void changeX(int x);
	void changeY(int y);
	void setX(int x);
	void setY(int y);
	void changeSize(int deltaX, int deltaY);
	void resetSize();

	Actor(int x, int y);
	virtual ~Actor();
};

#endif

