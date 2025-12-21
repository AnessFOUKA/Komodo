#include "AnimatedImage.h"

std::string AnimatedImage::getImgId(){
    return imgId;
}
float AnimatedImage::getX(){
    return x;
}
float AnimatedImage::getY(){
    return y;
}
std::vector<std::vector<float>> AnimatedImage::getImageCoords(){
    return imageCoords;
}
float AnimatedImage::getImageCoordsIndex(){
    return imageCoordsIndex;
}
float AnimatedImage::getAnimationSpeed(){
    return animationSpeed;
}

void AnimatedImage::setImgId(std::string imgId){
    this->imgId=imgId;
}
void AnimatedImage::setX(float x){
    this->x=x;
}
void AnimatedImage::setY(float y){
    this->y=y;
}
void AnimatedImage::setImageCoords(std::vector<std::vector<float>> imageCoords){
    this->imageCoords=imageCoords;
}
void AnimatedImage::setImageCoordsIndex(float imageCoordsIndex){
    this->imageCoordsIndex=imageCoordsIndex;
}
void AnimatedImage::setAnimationSpeed(float animationSpeed){
    this->animationSpeed=animationSpeed;
}

void AnimatedImage::step(){
    for(auto& i:scriptsList){
        i.loadScript();
    }
    std::vector<float>& imageCoord=imageCoords[(int)imageCoordsIndex];
    float& imageX=imageCoord[0];
    float& imageY=imageCoord[1];
    float& imageWidth=imageCoord[2];
    float& imageHeight=imageCoord[3];
    int imageCoordsSize=imageCoords.size();
    Game* trueGameInstance=static_cast<Game*>(gameInstance);
    width=imageWidth;
    height=imageHeight;
    if(cameras.size()>0){
for(auto* i:cameras){
            i->pushCameraGraphicOrder(imgId,x,y,imageX,imageY,imageWidth,imageHeight,scaleX,scaleY,trueGameInstance);
        }
    }else{
        trueGameInstance->addGraphicOrder(imgId,x,y,imageX,imageY,imageWidth,imageHeight,scaleX,scaleY);
    }
    if(imageCoordsIndex<imageCoordsSize){
        imageCoordsIndex+=animationSpeed*trueGameInstance->getDt();
    }
    
    if(imageCoordsIndex>=imageCoordsSize){
        imageCoordsIndex=0;
    }
}

float AnimatedImage::getWidth(){
    return width;
}

float AnimatedImage::getHeight(){
    return height;
}

float AnimatedImage::getScaleX(){
    return scaleX;
}

float AnimatedImage::getScaleY(){
    return scaleY;
}

void AnimatedImage::setScaleX(float scaleX){
    this->scaleX=scaleX;
}

void AnimatedImage::setScaleY(float scaleY){
    this->scaleY=scaleY;
}