#include <Collider.h>

float Collider::getX(){
    return x;
}
float Collider::getY(){
    return y;
}
float Collider::getWidth(){
    return width;
}
float Collider::getHeight(){
    return height;
}

void Collider::setX(float x){
    this->x=x;
}
void Collider::setY(float y){
    this->y=y;
}
void Collider::setWidth(float width){
    this->width=width;
}
void Collider::setHeight(float height){
    this->height=height;
}

collideSides Collider::checkCollision(Collider* collider){
    collideSides sides={false,false,false,false,false};
    if(detectInbound(x,y,width,height,collider->x,collider->y,collider->width,collider->height)){
        float xCollisionZoneLength=std::min(x+width,collider->x+collider->width)-std::max(x,collider->x);
        float yCollisionZoneLength=std::min(y+height,collider->y+collider->height)-std::max(y,collider->y);
        if(yCollisionZoneLength>xCollisionZoneLength){
            float xDistance=(this->x+this->width/2)-(collider->getX()+collider->getWidth()/2);
            if(xDistance<0){
                sides.left=true;
            }
            else{
                sides.right=true;
            }
        }else{
            float yDistance=(this->y+this->height/2)-(collider->getY()+collider->getHeight()/2);
            if(yDistance<0){
                sides.up=true;
            }
            else{
                sides.down=true;
            }
        }
        sides.collideTrue=(sides.up||sides.down||sides.left||sides.right);
    }
    return sides;
}