#include "StdController.hpp"

void StdController::checkInput(){
    
}

void StdController::updateKeysState(){
    #ifdef PLATFORM_3DS
    hidScanInput();

    u32 down=hidKeysHeld();
    
    circlePosition cp;
    hidCircleRead(&cp);

    touchPosition tp;
    hidTouchRead(&tp);
    #endif

    #ifdef PLATFORM_PSVITA
    sceCtrlReadBufferPositive(0,&vitaCtrlData,1);
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
    sceTouchRead(SCE_TOUCH_PORT_FRONT,&sceTouchData,1);
    sceTouchRead(SCE_TOUCH_PORT_BACK,&sceRearTouchPanelData,1);
    #endif

    std::unordered_map<std::string,u_int32_t> keys={
        #ifdef PLATFORM_3DS
        {"3ds_a",KEY_A},
        {"3ds_b",KEY_B},
        {"3ds_x",KEY_X},
        {"3ds_y",KEY_Y},
        #endif
        #ifdef PLATFORM_PSVITA
        {"vita_circle",SCE_CTRL_CIRCLE},
        {"vita_cross",SCE_CTRL_CROSS},
        {"vita_triangle",SCE_CTRL_TRIANGLE},
        {"vita_square",SCE_CTRL_SQUARE},
        #endif
        
    };
    for(auto& [key_id,key] : keys){
        if(keysFormerState.find(key_id)==keysFormerState.end())keysFormerState[key_id]={0};
        keysState[key_id]={
            #ifdef PLATFORM_3DS
            static_cast<float>(static_cast<bool>(down & key))
            #endif
            #ifdef PLATFORM_PSVITA
            static_cast<float>(static_cast<bool>(vitaCtrlData.buttons & key))
            #endif 
        };
        downKeys[key_id]={
            static_cast<float>(keysState[key_id]==std::vector<float>{1} && keysFormerState[key_id]==std::vector<float>{0})
        };

        keysFormerState[key_id]=keysState[key_id];
    }


    std::unordered_map<std::string,std::vector<float>> altInputs={
        #ifdef PLATFORM_3DS
        {
            "3ds_dpad",
            {
                static_cast<float>(((down & KEY_DRIGHT)!=0) - ((down & KEY_DLEFT)!=0)),
                static_cast<float>(((down & KEY_DDOWN)!=0) - ((down & KEY_DUP)!=0))
                #ifdef PLATFORM_PSVITA
                static_cast<float>(((vitaCtrlData.buttons & SCE_CTRL_RIGHT)!=0) - ((vitaCtrlData.buttons & SCE_CTRL_LEFT)!=0)),
                static_cast<float>(((vitaCtrlData.buttons & SCE_CTRL_DOWN)!=0) - ((vitaCtrlData.buttons & SCE_CTRL_UP)!=0))
                #endif              
            }
        },
        {
            "3ds_stick",
            {
                static_cast<float>(static_cast<int>(cp.dx)/154),
                static_cast<float>(static_cast<int>(cp.dy)/-154)
            }
        },
        {
            "3ds_touchScreen",
            {
                static_cast<float>(tp.px),
                static_cast<float>(tp.py)
            }
        }
        #endif
        #ifdef PLATFORM_PSVITA
        {
            "vita_dpad",
            {
                static_cast<float>(((vitaCtrlData.buttons & SCE_CTRL_RIGHT)!=0) - ((vitaCtrlData.buttons & SCE_CTRL_LEFT)!=0)),
                static_cast<float>(((vitaCtrlData.buttons & SCE_CTRL_DOWN)!=0) - ((vitaCtrlData.buttons & SCE_CTRL_UP)!=0))              
            }
        },
        {
            "vita_lstick",
            {
                static_cast<float>(static_cast<int>(vitaCtrlData.lx - 127)/ 127),
                static_cast<float>(static_cast<int>(vitaCtrlData.ly - 127)/ 127)
            }
        },
        {
            "vita_rstick",
            {
                static_cast<float>(static_cast<int>(vitaCtrlData.rx - 127)/ 127),
                static_cast<float>(static_cast<int>(vitaCtrlData.ry - 127)/ 127)
            }
        },
        #endif
    };

    #ifdef PLATFORM_PSVITA
    for(size_t touchIndex=0;touchIndex<6;touchIndex++){
        altInputs["vita_touchScreen_"+std::to_string(touchIndex+1)]={
            static_cast<float>(sceTouchData.report[touchIndex].x),
            static_cast<float>(sceTouchData.report[touchIndex].y)
        };
        if(touchIndex<4){
            altInputs["vita_rearTouchPanel_"+std::to_string(touchIndex+1)]={
                static_cast<float>(sceRearTouchPanelData.report[touchIndex].x),
                static_cast<float>(sceRearTouchPanelData.report[touchIndex].y)
            };
        }
    }
    #endif

    for(auto& [inputGroupId,floatList] : altInputs){
        keysState[inputGroupId]=floatList;
        if(inputGroupId.find("stick")==inputGroupId.npos){
            if(keysFormerState.find(inputGroupId)==keysFormerState.end())keysFormerState[inputGroupId]={0,0};
            downKeys[inputGroupId]={
                0,
                0
            };

            if((keysFormerState[inputGroupId]==std::vector<float>{0,0})){
                downKeys[inputGroupId]=keysState[inputGroupId];
            }
            keysFormerState[inputGroupId]=keysState[inputGroupId];
        }
    }
}


/*
1919 -> 960 
rx -> sx=(rx*960)/1919
*/