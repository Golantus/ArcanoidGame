#include "actor.h"
#ifndef BRICK
#define BRICK

class Brick : public Actor {

private:
    bool isRed;
    bool isDestroyed;
public:
    bool getDestroyed();
    void setDestroyed(bool destroyed);
    bool getIsRed();
    Brick(int x, int y, bool isRed);
    ~Brick();
};

#endif