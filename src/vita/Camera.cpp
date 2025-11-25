#include <Camera.h>

std::vector<std::vector<int>> Camera::getRenderers(){
    return renderers;
}
int Camera::getCameraX(){
    return cameraX;
}
int Camera::getCameraY(){
    return cameraY;
}

void Camera::setRenderers(std::vector<std::vector<int>> renderers){
    this->renderers=renderers;
}
void Camera::setCameraX(int cameraX){
    this->cameraX=cameraX;
}
void Camera::setCameraY(int cameraY){
    this->cameraY=cameraY;
}