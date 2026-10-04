#include "ErrorHandler.hpp"

std::vector<Error> ErrorHandler::errors={};
bool ErrorHandler::interrupt=false;
size_t ErrorHandler::errorIndex=0;

void ErrorHandler::manageErrors(){
    interrupt=errors.size()>0;
    if(interrupt){
        GraphicsManager::drawText({errors[errorIndex].text},0,0,0,1.0f,255,{"std_cam"},0);
    }
}

void ErrorHandler::sendError(u_int16_t code, std::string text){
    if(!interrupt)errors.push_back({code,text});
}

bool ErrorHandler::getInterrupt(){
    return interrupt;
}