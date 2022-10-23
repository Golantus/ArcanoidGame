#include "platform.h"

void Platform::move(int dx) {
    posX += dx;
}

void Platform::reset() {
    posX = startX;
    posY = startY;
}

Platform::Platform(int x, int y) :Actor(x, y) {
    startX = x;
    startY = y;
}

Platform::~Platform() {}