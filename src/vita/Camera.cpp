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

void Camera::pushCameraGraphicOrder(std::string imgId,int x,int y,int imageX,int imageY,int imageWidth,int imageHeigth,float scaleX,float scaleY,GameObject* gameInstance){
    for(auto renderer : renderers){
        int rendererX=renderer[0];
        int rendererY=renderer[1];
        int rendererWidth=renderer[2];
        int rendererHeigth=renderer[3];
        if(detectInbound(x,y,imageWidth*scaleX,imageHeigth*scaleY,rendererX,rendererY,rendererWidth,rendererHeigth)){
            int worldXTemp=x-(cameraX-rendererX);
            int worldYTemp=y-(cameraY-rendererY);
            int imageXTemp=imageX;
            int imageYTemp=imageY;
            int imageWidthTemp=imageWidth;
            int imageHeigthTemp=imageHeigth;

            if(worldXTemp<rendererX){
                int overflow=rendererX-worldXTemp;
                imageXTemp+=overflow;
                imageWidthTemp-=overflow;
                worldXTemp=rendererX;
            }

            if(worldYTemp<rendererY){
                int overflow=rendererY-worldYTemp;
                imageYTemp+=overflow;
                imageHeigthTemp-=overflow;
                worldYTemp=rendererY;
            }

            if(worldXTemp+imageWidthTemp*scaleX>rendererX+rendererWidth){
                int overflow=(worldXTemp+imageWidthTemp*scaleX)-(rendererX+rendererWidth);
                imageWidthTemp-=(overflow/scaleX);
            }

            if(worldYTemp+imageHeigthTemp*scaleY>rendererY+rendererHeigth){
                int overflow=(worldYTemp+imageHeigthTemp*scaleY)-(rendererY+rendererHeigth);
                imageHeigthTemp-=(overflow/scaleY);
            }

            gameInstance->addGraphicOrder(imgId,worldXTemp,worldYTemp,imageXTemp,imageYTemp,imageWidthTemp,imageHeigthTemp,scaleX,scaleY);

        }
    }
}