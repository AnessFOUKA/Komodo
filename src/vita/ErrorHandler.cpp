#include "ErrorHandler.h"

int handleFolder(){
    SceIoStat stat;
    if(sceIoGetstat("ux0:/data/KomodoLogs",&stat)<0){
        int mkdirAttempt=sceIoMkdir("ux0:/data/KomodoLogs",0777);
        if(mkdirAttempt<0){
            return -1;
        }
    }
    return 0;
}

std::string saveLog(Error error,std::string path){
    if(path.size()==0){
        return "path length must be higher than 0";
    }
    int folderHandlingResult=handleFolder();
    if(folderHandlingResult<0){
        return "folder creation error";
    }
    int fd=sceIoOpen(("ux0:/data/KomodoLogs/"+path).c_str(),SCE_O_WRONLY | SCE_O_APPEND | SCE_O_CREAT,0777);
    if(fd<0){
        return "log file creation error";
    }
    int writeToFileAttempt=sceIoWrite(
        fd,
        (std::to_string(error.type)+" : "+error.message+"\n").c_str(),
        (std::to_string(error.type)+" : "+error.message+"\n").size()
    );
    if(writeToFileAttempt<0){
        return "log file writing error";
    }
    int closeFileAttempt=sceIoClose(fd);
    if(closeFileAttempt<0){
        return "log file closing error";
    }
    return "";
}

ErrorHandler::ErrorHandler(vita2d_pvf** pvf,InputManager* inputManager):
    errorStack({}),
    logFilePath(""),
    logSavingError(""),
    errorStackCursor(0),
    pvf(pvf),
    showErrorScreen(false),
    inputManager(inputManager),
    allowErrorScreens(true)
{
    inputManager->addKey("previousError",SCE_CTRL_LEFT);
    inputManager->addKey("nextError",SCE_CTRL_RIGHT);
}

void ErrorHandler::manageErrors(){
    if(!this->showErrorScreen){
        for(Error& error : errorStack){
            if(error.saveToLogs){
                std::string logSavingAttempt=saveLog(error,this->logFilePath);
                if(logSavingAttempt.size()>0){
                    this->logSavingError=logSavingAttempt;
                }
            }    
            this->showErrorScreen=(error.showErrorScreen||this->logSavingError.size()>0)&&allowErrorScreens;
        }
    }else{
        if(*pvf!=nullptr){
            vita2d_pvf_draw_text(*pvf,420,200,RGBA8(255,255,255,255),1.0f,this->logSavingError.c_str());
            if(this->errorStack.size()>0){
                vita2d_pvf_draw_text(*pvf,420,250,RGBA8(255,255,255,255),1.0f,("erreur "+std::to_string(this->errorStackCursor+1)+"/"+std::to_string(this->errorStack.size())).c_str());
                vita2d_pvf_draw_text(*pvf,420,300,RGBA8(255,255,255,255),1.0f,("type :"+std::to_string(this->errorStack[this->errorStackCursor].type)+" message : "+this->errorStack[this->errorStackCursor].message).c_str()); 
            }
            errorStackCursor+=static_cast<int>(inputManager->checkClicked("nextError") && errorStackCursor<errorStack.size()-1);
            errorStackCursor-=static_cast<int>(inputManager->checkClicked("previousError") && errorStackCursor>0);
        }
    }
}

void ErrorHandler::setLogFilePath(std::string logFilePath){
    this->logFilePath=logFilePath;
}
std::string ErrorHandler::getLogFilePath(){
    return logFilePath;
}

bool ErrorHandler::getShowErrorScreen(){
    return showErrorScreen;
}

bool ErrorHandler::getAllowErrorScreens(){
    return allowErrorScreens;
}

void ErrorHandler::setAllowErrorScreens(bool allowErrorScreens){
    this->allowErrorScreens=allowErrorScreens;
}

void ErrorHandler::sendError(int type,std::string message,bool showErrorScreen,bool saveToLogs){
    this->errorStack.push_back({type,message,showErrorScreen,saveToLogs});
}