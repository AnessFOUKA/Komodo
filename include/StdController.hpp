#ifndef STDCONTROLLER_H
#define STDCONTROLLER_H

#include "Controller.hpp"

//#define PLATFORM_PSVITA
//#define PLATFORM_3DS

#ifdef PLATFORM_PSVITA
#include <psp2/ctrl.h>
#include <psp2/touch.h>
#include <string.h>
#endif

#ifdef PLATFORM_3DS
#include <3ds.h>
#endif

class StdController : public Controller {
    private:
        #ifdef PLATFORM_PSVITA
        SceCtrlData vitaCtrlData;
        SceTouchData sceTouchData;
        SceTouchData sceRearTouchPanelData;
        #endif
    public:
        #ifdef PLATFORM_PSVITA
        StdController():
            vitaCtrlData(),
            sceTouchData(),
            sceRearTouchPanelData()

        {
            memset(&vitaCtrlData,0,sizeof(vitaCtrlData));
            memset(&sceTouchData,0,sizeof(sceTouchData));
            memset(&sceRearTouchPanelData,0,sizeof(sceRearTouchPanelData));
        }
        #endif
        void updateKeysState();
        void checkInput();
};

#endif