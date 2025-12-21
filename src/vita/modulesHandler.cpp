#include "modulesHandler.h"
bool detectInbound(float x1,float y1,float width1,float heigth1,float x2,float y2,float width2,float heigth2){
    return !(
        x1+width1<x2 ||
        x1>x2+width2 ||
        y1+heigth1<y2 ||
        y1>y2+heigth2 
    );
}