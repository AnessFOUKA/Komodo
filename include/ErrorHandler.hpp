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

#include "GraphicsManager.hpp"

struct Error{
    u_int16_t code;
    std::string text;
};

class ErrorHandler{
    
    static std::vector<Error> errors;
    static bool interrupt;
    static size_t errorIndex;
    
    public:
        static void sendError(u_int16_t code, std::string text);
        static void manageErrors();
        static bool getInterrupt();
};

#endif