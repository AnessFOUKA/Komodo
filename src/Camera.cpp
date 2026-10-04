#include "Camera.hpp"

float Camera::getCx(){
    return cx;
}

float Camera::getCy(){
    return cy;
}

void Camera::setCx(float cx){
    this->cx=cx;
}

void Camera::setCy(float cy){
    this->cy=cy;
}

float Camera::getRx(){
    return rx;
}

float Camera::getRy(){
    return ry;
}

float Camera::getRw(){
    return rw;
}

float Camera::getRh(){
    return rh;
}

void Camera::setRx(float rx){
    this->rx=rx;
}

void Camera::setRy(float ry){
    this->ry=ry;
}

void Camera::setRw(float rw){
    this->rw=rw;
}

void Camera::setRh(float rh){
    this->rh=rh;
}