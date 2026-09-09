#include "Collider.hpp"

Collider::Collider(float x, float y, float width, float height)
	: x(x), y(y), width(width), height(height){
}

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
	this->x = x;
}

void Collider::setY(float y){
	this->y = y;
}

void Collider::setWidth(float width){
	this->width = width;
}

void Collider::setHeight(float height){
	this->height = height;
}

CollisionState Collider::checkCollision(Collider* collider){
	float collisionZoneX=std::min(x+width,collider->getX()+collider->getWidth())-std::max(x,collider->getX());
	float collisionZoneY=std::min(y+height,collider->getY()+collider->getHeight())-std::max(y,collider->getY());
	if(collisionZoneX>=0 && collisionZoneY>=0){
		float collider1Center[2]={x+width/2, y+height/2};
		float collider2Center[2]={collider->getX()+collider->getWidth()/2, collider->getY()+collider->getHeight()/2};
		return (CollisionState){
			.directionVector={
				collider2Center[0]-collider1Center[0],
				collider2Center[1]-collider1Center[1]		
			},
			.collisionType=collisionZoneY>=collisionZoneX?HORIZONTAL_COLLISION:VERTICAL_COLLISION
		};
	}else{
		return (CollisionState){
			.directionVector={0,0},
			.collisionType=NULL_COLLISION
		};
	}
}