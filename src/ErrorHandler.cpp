#include "ErrorHandler.hpp"

std::vector<Error> ErrorHandler::errors={};
bool ErrorHandler::showLogs=false;
bool ErrorHandler::interrupt=false;
bool ErrorHandler::initialized=false;

#ifdef PLATFORM_3DS
C2D_Font ErrorHandler::sysfont;
#endif

#ifdef PLATFORM_PSVITA
vita2d_pvf* ErrorHandler::sysfont;
#endif

void ErrorHandler::manageErrors(){
    if(!initialized){
        #ifdef PLATFORM_3DS
        sysfont=C2D_FontLoadSystem(CFG_REGION_EUR);
        #endif
        #ifdef PLATFORM_PSVITA
        sysfont=vita2d_load_default_pvf();
        #endif
        initialized=true;
    }
    for(auto& error : errors){
        if(interrupt==false){
            interrupt=error.interrupt;
        }
        #ifdef PLATFORM_3DS
        if(!error.initialized){
            error.textBuffer=C2D_TextBufNew(4096);
            error.initialized=true;
        }
        C2D_TextBufClear(error.textBuffer);
        C2D_TextFontParse(&error.textGPU,sysfont,error.textBuffer,error.text.c_str());
        C2D_TextOptimize(&error.textGPU);
        C2D_DrawText(&error.textGPU,C2D_WithColor,error.x,error.y,0,0.5f,0.5f,C2D_Color32(255,255,255,255));
        #endif
        #ifdef PLATFORM_PSVITA
        vita2d_pvf_draw_text(sysfont,error.x,error.y,RGBA8(255,255,255,255),1.0f,error.text.c_str());
        #endif
    }
    #if defined(PLATFORM_3DS) || defined(PLATFORM_PSVITA)
    if(!interrupt){
        clearErrors();
    }
    #endif
}

#ifdef PLATFORM_3DS
void ErrorHandler::sendError(uint16_t code, std::string text, bool interrupt, uint16_t x, uint16_t y){
    Error newError;
    newError.code=code;
    newError.text=text;
    newError.interrupt=interrupt;
    newError.initialized=false;
    newError.x=x;
    newError.y=y;
    errors.push_back(newError);
}
#endif
#ifdef PLATFORM_PSVITA
void ErrorHandler::sendError(uint16_t code, std::string text, bool interrupt, uint16_t x, uint16_t y){
    errors.push_back({code,x,y,text,interrupt});
}
#endif

void ErrorHandler::clearErrors(){
    #ifdef PLATFORM_3DS
    for(auto& error : errors){
        C2D_TextBufDelete(error.textBuffer);
    }
    #endif
    errors={};
}