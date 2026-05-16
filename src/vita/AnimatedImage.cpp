#include "AnimatedImage.h"

AnimatedImage::AnimatedImage(
    std::string imgId,
    float x,
    float y,
    std::vector<ImageCoord> imageCoords,
    float imageCoordsIndex,
    float animationSpeed,
    float scaleX,
    float scaleY,
    float alpha,
    int layer,
    std::string anchorInfos,
    std::vector<std::string> idsList,
    std::vector<std::string> scriptsIds
):
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
    layer(layer),
    anchorInfos(anchorInfos),
    globalX(0),
    globalY(0),
    globalScaleX(scaleX),
    globalScaleY(scaleY),
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
    //faire une différence sémantique entre coordonnées globales et locales
    ItemHandler* motherConverted=static_cast<ItemHandler*>(mother);
    globalScaleX=scaleX*motherConverted->getGlobalScaleX();
    globalScaleY=scaleY*motherConverted->getGlobalScaleY();
    globalX=(x*motherConverted->getGlobalScaleX()+motherConverted->getGlobalX());
    globalY=(y*motherConverted->getGlobalScaleY()+motherConverted->getGlobalY());
    if(imageCoordsIndex>=0&& imageCoordsIndex<imageCoords.size()){
        ImageCoord& imageCoord=imageCoords[static_cast<int>(imageCoordsIndex)];
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
        manageAnchorPoint(anchorInfos,globalX,globalY,getWidth(),getHeight(),gameInstance);
        if(cameras.size()>0){
            for(auto* i:cameras){
                i->pushCameraGraphicOrder(imgId,globalX,globalY,imageX,imageY,imageWidth,imageHeight,globalScaleX,globalScaleY,alpha,layer,trueGameInstance);
            }
        }else{
            trueGameInstance->addGraphicOrder(imgId,globalX,globalY,imageX,imageY,imageWidth,imageHeight,globalScaleX,globalScaleY,alpha,layer);
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
    return width*globalScaleX;
}

float AnimatedImage::getHeight(){
    return height*globalScaleY;
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

std::string AnimatedImage::getAnchorInfos(){
    return anchorInfos;
}

void AnimatedImage::setAnchorInfos(std::string anchorInfos){
    this->anchorInfos=anchorInfos;
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
                float itemHighestPosition=potentialAnimatedImage->getGlobalX()+((*potentialAnimatedImage->getImageCoords())[potentialAnimatedImage->getImageCoordsIndex()].width*potentialAnimatedImage->getGlobalScaleX());
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
                float itemHighestPosition=potentialAnimatedImage->getGlobalY()+((*potentialAnimatedImage->getImageCoords())[potentialAnimatedImage->getImageCoordsIndex()].height*potentialAnimatedImage->getGlobalScaleY());
                if(itemHighestPosition>height || first){
                    height=itemHighestPosition;
                    first=false;
                }
            }
        }
    }
    return height;
}

float AnimatedImage::getGlobalX(){
    return globalX;
}

float AnimatedImage::getGlobalY(){
    return globalY;
}

float AnimatedImage::getGlobalScaleX(){
    return globalScaleX;
}

float AnimatedImage::getGlobalScaleY(){
    return globalScaleY;
}

void AnimatedImage::init(){
    ItemHandler* motherConverted=static_cast<ItemHandler*>(mother);
    globalScaleX=scaleX*motherConverted->getGlobalScaleX();
    globalScaleY=scaleY*motherConverted->getGlobalScaleY();
    globalX=(x*motherConverted->getGlobalScaleX()+motherConverted->getGlobalX());
    globalY=(y*motherConverted->getGlobalScaleY()+motherConverted->getGlobalY());
}