#include <Camera.h>

std::vector<std::vector<float>> Camera::getRenderers(){
    return renderers;
}
float Camera::getCameraX(){
    return cameraX;
}
float Camera::getCameraY(){
    return cameraY;
}

void Camera::setRenderers(std::vector<std::vector<float>> renderers){
    this->renderers=renderers;
}
void Camera::setCameraX(float cameraX){
    this->cameraX=cameraX;
}
void Camera::setCameraY(float cameraY){
    this->cameraY=cameraY;
}