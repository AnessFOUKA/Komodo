#include "AnimationComponent.hpp"

std::vector<AnimationFrame>* AnimationComponent::getFrames(){
    return &frames;
}

std::string AnimationComponent::getTexturePath(){
    return texturePath;
}

std::vector<std::string>* AnimationComponent::getCamIds(){
    return &cam_ids;
}

float AnimationComponent::getFrameIndex(){
    return frameIndex;
}

float AnimationComponent::getAnimationSpeed(){
    return animationSpeed;
}

float AnimationComponent::getX(){
    return x;
}

float AnimationComponent::getY(){
    return y;
}

float AnimationComponent::getScaleX(){
    return scaleX;
}

float AnimationComponent::getScaleY(){
    return scaleY;
}

float AnimationComponent::getAlpha(){
    return alpha;
}

int AnimationComponent::getLayer(){
    return layer;
}

size_t AnimationComponent::getScreenIndex(){
    return screenIndex;
}

Anchor AnimationComponent::getAnchor(){
    return anchor;
}

void AnimationComponent::setTexturePath(std::string texturePath){
    this->texturePath = texturePath;
}

void AnimationComponent::setFrameIndex(float frameIndex){
    this->frameIndex = frameIndex;
}

void AnimationComponent::setAnimationSpeed(float animationSpeed){
    this->animationSpeed = animationSpeed;
}

void AnimationComponent::setX(float x){
    this->x = x;
}

void AnimationComponent::setY(float y){
    this->y = y;
}

void AnimationComponent::setScaleX(float scaleX){
    this->scaleX = scaleX;
}

void AnimationComponent::setScaleY(float scaleY){
    this->scaleY = scaleY;
}

void AnimationComponent::setAlpha(float alpha){
    this->alpha = alpha;
}

void AnimationComponent::setLayer(int layer){
    this->layer = layer;
}

void AnimationComponent::setScreenIndex(size_t screenIndex){
    this->screenIndex = screenIndex;
}

void AnimationComponent::setAnchor(Anchor anchor){
    this->anchor = anchor;
}

void AnimationComponent::onLoop(){
    if(frameIndex>=0 && frameIndex<frames.size()){
        AnimationFrame* frame=&frames[frameIndex];    
        GraphicsManager::drawTexturePart(
            texturePath, 
            x, 
            y, 
            frame->imageX, 
            frame->imageY, 
            frame->imageWidth, 
            frame->imageHeight, 
            scaleX, 
            scaleY, 
            alpha, 
            layer, 
            anchor, 
            cam_ids, 
            screenIndex
        );
        if(frame->frameTimer<frame->endFrameTime){
            frame->frameTimer+=animationSpeed*Komodo::getDt();
        }else{
            frame->frameTimer=0;
            frameIndex++;
        }
    }else{
        frameIndex=0;
    }
}