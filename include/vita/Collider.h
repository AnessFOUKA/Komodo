#ifndef COLLIDER_H
#define COLLIDER_H

#include <modulesHandler.h>

struct collideSides{
    bool up;
    bool down;
    bool left;
    bool right;
    bool collideTrue;
};

class Collider{
    private:
        float x;
        float y;
        float width;
        float height;
    public:
        Collider(float x,float y,float width,float height):
            x(x),
            y(y),
            width(width),
            height(height)
        {}
        float getX();
        float getY();
        float getWidth();
        float getHeight();

        void setX(float x);
        void setY(float y);
        void setWidth(float width);
        void setHeight(float height);
        collideSides checkCollision(Collider* collider);
};

#endif