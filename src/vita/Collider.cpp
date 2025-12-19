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
    if(detectInbound(x-50,y-50,width+50,height+50,collider->x-50,collider->y-50,collider->width+50,collider->height+50)){
        float xCollisionZoneLength=std::min(x+width,collider->x+collider->width)-std::max(x,collider->x);
        float yCollisionZoneLength=std::min(y+height,collider->y+collider->height)-std::max(y,collider->y);
        if(yCollisionZoneLength>xCollisionZoneLength){
            if(x+width>=collider->x&&x+width<collider->x+(collider->width/2)){
                sides.left=true;
            }
            if(x<=collider->x+collider->width&&x>collider->x+(collider->width/2)){
                sides.right=true;
            }
        }else{
            if(y+height>=collider->y&&y+height<collider->y+(collider->height/2)){
                sides.up=true;
            }
            if(y<=collider->y+collider->height&&y>collider->y+(collider->height/2)){
                sides.down=true;
            }
        }
        sides.collideTrue=(sides.up||sides.down||sides.left||sides.right);
    }
    return sides;
}