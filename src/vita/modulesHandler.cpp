#include "modulesHandler.h"
bool detectInbound(float x1,float y1,float width1,float heigth1,float x2,float y2,float width2,float heigth2){
    return !(
        x1+width1<x2 ||
        x1>x2+width2 ||
        y1+heigth1<y2 ||
        y1>y2+heigth2 
    );
}

getFileTextReturn getFileText(std::string filename){
    SceIoStat stat;
    if(sceIoGetstat(filename.c_str(),&stat)<0){
        return {"","file does not exists"};
    }
    std::string fileText="";
    char buffer[256];
    int fd=sceIoOpen(filename.c_str(),SCE_O_RDONLY,0777);
    if(fd<0){
        return {"","file failed to be opened"};
    }
    int readedLinesAmount=0;
    while((readedLinesAmount=sceIoRead(fd,buffer,255))>0){
        buffer[readedLinesAmount]='\0';
        fileText.append(buffer);
    }
    if(readedLinesAmount<0){
        return {"","file failed to be readed"};
    }
    int fileClosingAttempt=sceIoClose(fd);
    if(fileClosingAttempt<0){
        return {"","file failed to be closed"};
    }
    return {fileText,""};
}