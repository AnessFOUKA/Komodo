#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#ifdef PLATFORM_3DS
#include <3ds.h>
#include <citro2d.h>
#endif

#ifdef PLATFORM_PSVITA
#include <vita2d.h>
#endif

#include <stdio.h>
#include <string>
#include <vector>

struct Error{
    #if defined(PLATFORM_3DS) || defined(PLATFORM_PSVITA)
    uint16_t code;
    uint16_t x;
    uint16_t y;
    #endif
    std::string text;
    bool interrupt;
    #ifdef PLATFORM_3DS
    C2D_TextBuf textBuffer;
    C2D_Text textGPU;
    bool initialized;
    #endif
};

class ErrorHandler{
    
    static std::vector<Error> errors;
    static bool showLogs;
    static bool interrupt;
    static bool initialized;
    #ifdef PLATFORM_3DS
    static C2D_Font sysfont;
    #endif

    #ifdef PLATFORM_PSVITA
    static vita2d_pvf* sysfont;
    #endif
    
    public:
        #if defined(PLATFORM_3DS) || defined(PLATFORM_PSVITA)
        static void sendError(uint16_t code, std::string text, bool interrupt, uint16_t x, uint16_t y);
        #endif
        static void manageErrors();
        static void clearErrors();
};

#endif