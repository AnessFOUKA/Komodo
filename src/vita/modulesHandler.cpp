#include "modulesHandler.h"
bool detectInbound(int x1,int y1,int width1,int heigth1,int x2,int y2,int width2,int heigth2){
    return !(
        x1+width1<x2 ||
        x1>x2+width2 ||
        y1+heigth1<y2 ||
        y1>y2+heigth2 
    );
}