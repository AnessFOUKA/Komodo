#include "AnimatedImage.h"

std::string AnimatedImage::getImgId(){
    return imgId;
}
int AnimatedImage::getX(){
    return x;
}
int AnimatedImage::getY(){
    return y;
}
std::vector<std::vector<int>> AnimatedImage::getImageCoords(){
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
void AnimatedImage::setX(int x){
    this->x=x;
}
void AnimatedImage::setY(int y){
    this->y=y;
}
void AnimatedImage::setImageCoords(std::vector<std::vector<int>> imageCoords){
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
    std::vector<int> imageCoord=imageCoords[(int)imageCoordsIndex];
    int imageX=imageCoord[0];
    int imageY=imageCoord[1];
    int imageWidth=imageCoord[2];
    int imageHeigth=imageCoord[3];
    int imageCoordsSize=imageCoords.size();
    Game* trueGameInstance=static_cast<Game*>(gameInstance);
    if(cameras.size()>0){
        for(auto* i:cameras){
            i->pushCameraGraphicOrder(imgId,x,y,imageX,imageY,imageWidth,imageHeigth,scaleX,scaleY,trueGameInstance);
        }
    }else{
        trueGameInstance->addGraphicOrder(imgId,x,y,imageX,imageY,imageWidth,imageHeigth,scaleX,scaleY);
    }
    if(imageCoordsIndex<imageCoordsSize){
        imageCoordsIndex+=animationSpeed*trueGameInstance->getDt();
    }
    
    if(imageCoordsIndex>=imageCoordsSize){
        imageCoordsIndex=0;
    }
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