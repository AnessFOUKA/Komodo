#ifndef COLLIDER_H
#define COLLIDER_H

#include <unordered_map>
#include <string>
#include <vector>

enum CollisionType{
    VERTICAL_COLLISION,
    HORIZONTAL_COLLISION,
    NULL_COLLISION
};

struct CollisionState{
    float directionVector[2];
    CollisionType collisionType;
};

class Collider{
    private:
        float x;
        float y;
        float width;
        float height;
    
    public:
        Collider(float x, float y, float width, float height);

        float getX();
        float getY();
        float getWidth();
        float getHeight();

        void setX(float x);
        void setY(float y);
        void setWidth(float width);
        void setHeight(float height);

        CollisionState checkCollision(Collider* collider);
};

#endif