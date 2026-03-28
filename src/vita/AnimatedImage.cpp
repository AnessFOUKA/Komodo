#include "AnimatedImage.h"

AnimatedImage::AnimatedImage(std::string imgId,float x,float y,std::vector<ImageCoord> imageCoords,float imageCoordsIndex,float animationSpeed,float scaleX,float scaleY,float alpha,std::vector<std::string> idsList,std::vector<std::string> scriptsIds):
    imgId(imgId),
    x(x),
    y(y),
    imageCoords(imageCoords),
    imageCoordsIndex(imageCoordsIndex),
    animationSpeed(animationSpeed),
    scaleX(scaleX),
    scaleY(scaleY),
    alpha(alpha),
    width(0),
    height(0),
    GameObject(idsList,scriptsIds)
{
    if(imageCoordsIndex>=0&&imageCoordsIndex<imageCoords.size()){
        width=imageCoords[imageCoordsIndex].width;
        height=imageCoords[imageCoordsIndex].height;
    }
}

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
    GameObject::step();
    if(mother==nullptr){
        return;
    }
    ItemHandler* motherConverted=static_cast<ItemHandler*>(mother);
    float xTemp=x+motherConverted->getX();
    float yTemp=y+motherConverted->getY();
    if(imageCoordsIndex>=0&& imageCoordsIndex<imageCoords.size()){
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
                i->pushCameraGraphicOrder(imgId,xTemp,yTemp,imageX,imageY,imageWidth,imageHeight,scaleX,scaleY,alpha,trueGameInstance);
            }
        }else{
            trueGameInstance->addGraphicOrder(imgId,xTemp,yTemp,imageX,imageY,imageWidth,imageHeight,scaleX,scaleY,alpha);
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
    }else{
        gameInstance->getMainErrorHandler()->sendError(4,"imageCoordsIndex out of imageCoords bounds",true,false);
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

float AnimatedImage::getAlpha(){
    return alpha;
}

void AnimatedImage::setAlpha(float alpha){
    this->alpha=alpha;
}

float ItemHandler::getWidth(){
    float width=0;
    bool first=true;
    for(auto& item:elements){
        auto* itemRawPtr=item.get();
        ItemHandler* potentialItemHandler=dynamic_cast<ItemHandler*>(itemRawPtr);
        AnimatedImage* potentialAnimatedImage=dynamic_cast<AnimatedImage*>(itemRawPtr);
        if(potentialItemHandler){
            float itemHandlerWidth=potentialItemHandler->getWidth();
            if(itemHandlerWidth>width || first){
                width=itemHandlerWidth;
                first=false;
            }
        }else if(potentialAnimatedImage){
            if(potentialAnimatedImage->getImageCoordsIndex()>=0 && potentialAnimatedImage->getImageCoordsIndex()<potentialAnimatedImage->getImageCoords()->size()){
                float itemHighestPosition=potentialAnimatedImage->getX()+((*potentialAnimatedImage->getImageCoords())[potentialAnimatedImage->getImageCoordsIndex()].width*potentialAnimatedImage->getScaleX());
                if(itemHighestPosition>width || first){
                    width=itemHighestPosition;
                    first=false;
                }
            }
        }
    }
    return width;
}

float ItemHandler::getHeight(){
    float height=0;
    bool first=true;
    for(auto& item:elements){
        auto* itemRawPtr=item.get();
        ItemHandler* potentialItemHandler=dynamic_cast<ItemHandler*>(itemRawPtr);
        AnimatedImage* potentialAnimatedImage=dynamic_cast<AnimatedImage*>(itemRawPtr);
        if(potentialItemHandler){
            float itemHandlerHeight=potentialItemHandler->getHeight();
            if(itemHandlerHeight>height || first){
                height=itemHandlerHeight;
                first=false;
            }
        }else if(potentialAnimatedImage){
            if(potentialAnimatedImage->getImageCoordsIndex()>=0 && potentialAnimatedImage->getImageCoordsIndex()<potentialAnimatedImage->getImageCoords()->size()){
                float itemHighestPosition=potentialAnimatedImage->getY()+((*potentialAnimatedImage->getImageCoords())[potentialAnimatedImage->getImageCoordsIndex()].height*potentialAnimatedImage->getScaleY());
                if(itemHighestPosition>height || first){
                    height=itemHighestPosition;
                    first=false;
                }
            }
        }
    }
    return height;
}

float AnimatedImage::getWorldX(){
    ItemHandler* motherConverted=static_cast<ItemHandler*>(mother);
    return (x+motherConverted->getX())*scaleX;
}

float AnimatedImage::getWorldY(){
    ItemHandler* motherConverted=static_cast<ItemHandler*>(mother);
    return (y+motherConverted->getY())*scaleY;
}