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
std::vector<ImageCoord>* AnimatedImage::getImageCoords(){
    return &imageCoords;
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
void AnimatedImage::setImageCoords(std::vector<ImageCoord> imageCoords){
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
    ItemHandler* motherConverted=static_cast<ItemHandler*>(mother);
    float xTemp=x+motherConverted->getX();
    float yTemp=y+motherConverted->getY();
    ImageCoord& imageCoord=imageCoords[(int)imageCoordsIndex];
    float& imageX=imageCoord.x;
    float& imageY=imageCoord.y;
    float& imageWidth=imageCoord.width;
    float& imageHeight=imageCoord.height;
    float& frameTimeMax=imageCoord.frameTimeMax;
    float& frameTimeIndex=imageCoord.frameTimeIndex;
    int imageCoordsSize=imageCoords.size();
    Game* trueGameInstance=static_cast<Game*>(gameInstance);
    width=imageWidth;
    height=imageHeight;
    if(cameras.size()>0){
        for(auto* i:cameras){
            i->pushCameraGraphicOrder(imgId,xTemp*scaleX,yTemp*scaleY,imageX,imageY,imageWidth,imageHeight,scaleX,scaleY,trueGameInstance);
        }
    }else{
        trueGameInstance->addGraphicOrder(imgId,xTemp*scaleX,yTemp*scaleY,imageX,imageY,imageWidth,imageHeight,scaleX,scaleY);
    }
    if(frameTimeIndex<frameTimeMax){
        frameTimeIndex+=animationSpeed*trueGameInstance->getDt();
    }

    if(frameTimeIndex>=frameTimeMax){
        imageCoordsIndex+=1;
        frameTimeIndex=0;
    }
    
    if(imageCoordsIndex>=imageCoordsSize){
        imageCoordsIndex=0;
    }
}

float AnimatedImage::getWidth(){
    return width*scaleX;
}

float AnimatedImage::getHeight(){
    return height*scaleY;
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

float ItemHandler::getWidth(){
    float width=0;
    for(auto& item:elements){
        auto* itemRawPtr=item.get();
        if(dynamic_cast<ItemHandler*>(itemRawPtr)){
            width=static_cast<ItemHandler*>(itemRawPtr)->getWidth();
        }else if(dynamic_cast<AnimatedImage*>(itemRawPtr)){
            AnimatedImage* animatedImageItemConverted=static_cast<AnimatedImage*>(itemRawPtr);
            float potentialGreaterCoordinate=animatedImageItemConverted->getX()+animatedImageItemConverted->getWidth();
            if(potentialGreaterCoordinate>width){
                width=potentialGreaterCoordinate;
            }
        }
    }
    return width;
}

float ItemHandler::getHeight(){
    float height=0;
    for(auto& item:elements){
        auto* itemRawPtr=item.get();
        if(dynamic_cast<ItemHandler*>(itemRawPtr)){
            height=static_cast<ItemHandler*>(itemRawPtr)->getHeight();
        }else if(dynamic_cast<AnimatedImage*>(itemRawPtr)){
            AnimatedImage* animatedImageItemConverted=static_cast<AnimatedImage*>(itemRawPtr);
            float potentialGreaterCoordinate=animatedImageItemConverted->getY()+animatedImageItemConverted->getHeight();
            if(potentialGreaterCoordinate>height){
                height=potentialGreaterCoordinate;
            }
        }
    }
    return height;
}