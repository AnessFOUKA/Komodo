#include "GraphicsManager.hpp"

#ifdef PLATFORM_3DS
std::vector<C3D_RenderTarget*> GraphicsManager::screens={
    C2D_CreateScreenTarget(GFX_TOP,GFX_LEFT),
    C2D_CreateScreenTarget(GFX_BOTTOM,GFX_LEFT)
};
C2D_Font GraphicsManager::sysfont=C2D_FontLoadSystem(CFG_REGION_USA);

#endif

#ifdef PLATFORM_PSVITA
vita2d_pvf* GraphicsManager::sysfont=vita2d_load_default_pvf();
#endif

std::vector<std::unordered_map<std::string,std::unordered_map<std::string, std::vector<GraphicOrder>>>> GraphicsManager::texturePipeline={
    {},
    {}
};

std::vector<std::unordered_map<std::string,std::vector<TextOrder>>> GraphicsManager::textPipeline={
    {},
    {}
};

std::unordered_map<std::string, Camera> GraphicsManager::cameras={
};

void GraphicsManager::setClipRectangle(int x1, int y1, int x2, int y2, int screenWidth, int screenHeight){

    for(std::vector<int*> coords : std::vector<std::vector<int*>>{{&x1,&x2,&screenWidth},{&y1,&y2,&screenHeight}}){
        if(*coords[0]<0){
            if(*coords[1]<0){
                for(size_t index=0;index<2;index++){
                    *coords[index]=0;
                }
            }else{
                *coords[0]=0;
            }
        }

        if(*coords[1]>*coords[2]){
            if(*coords[0]>*coords[2]){
                for(size_t index=0;index<2;index++){
                    *coords[index]=*coords[2];
                }
            }else{
                *coords[1]=*coords[2];
            }
        }

        if(*coords[0]==*coords[1]){
            for(size_t index=0;index<2;index++){
                *coords[index]=0;
            }
        }
    }
    
    #ifdef PLATFORM_3DS

    C3D_SetScissor(GPU_SCISSOR_NORMAL,
        screenHeight-y2,
        screenWidth-x2,
        screenHeight-y1,
        screenWidth-x1
    );

    #endif

    #ifdef PLATFORM_PSVITA

    vita2d_set_clip_rectangle(x1,y1,x2,y2);

    #endif
}

void GraphicsManager::drawText(std::vector<std::string> lines, float x, float y, float gap, float scale, float alpha, std::vector<std::string> cam_ids, size_t screenIndex){
    TextOrder textOrder;
    textOrder.gap=gap;
    textOrder.lines=lines;
    textOrder.x=x;
    textOrder.y=y;
    textOrder.scale=scale;
    textOrder.alpha=alpha;
    if(screenIndex>=textPipeline.size()){
        ErrorHandler::sendError(2,"out of range screenIndex");
    }else{
        for(std::string& cam_id : cam_ids){
            textPipeline[screenIndex][cam_id].push_back(textOrder);
        }
    }
}

void GraphicsManager::drawTexturePart(
    std::string path, 
    float x, 
    float y, 
    float imageX, 
    float imageY, 
    float imageWidth, 
    float imageHeight,
    float scaleX,
    float scaleY,
    float alpha, 
    int layer,
    std::vector<std::string> cam_ids,
    size_t screenIndex
){
    if(screenIndex>=textPipeline.size()){
        ErrorHandler::sendError(2,"out of range screenIndex");
    }else{
        for(std::string& cam_id : cam_ids){
            texturePipeline[screenIndex][cam_id][path].push_back(GraphicOrder{
                .x=x,
                .y=y,
                .imageX=imageX,
                .imageY=imageY,
                .imageWidth=imageWidth,
                .imageHeight=imageHeight,
                .scaleX=scaleX,
                .scaleY=scaleY,
                .alpha=alpha,
                .layer=layer,
                .screenIndex=screenIndex
            });
        }
    }
}

void GraphicsManager::executeGraphicPipeline(){
    #ifdef PLATFORM_3DS
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
    #endif
    #ifdef PLATFORM_PSVITA
    vita2d_start_drawing();
    vita2d_clear_screen();
    vita2d_enable_clipping();
    #endif
    for(size_t screenIndex=0;screenIndex<texturePipeline.size();screenIndex++){
        #ifdef PLATFORM_3DS
        C2D_TargetClear(screens[screenIndex],C2D_Color32(0,0,0,255));
        #else
        if(screenIndex>0){
            break;
        }
        #endif
            for(auto& [cam_id, graphicOrdersDict] : texturePipeline[screenIndex]){
                Camera* camera=nullptr;
                #ifdef PLATFORM_3DS
                C2D_SceneBegin(screens[screenIndex]);
                float screensWidth[2]={400,320};
                float screensHeight[2]={240,240};
                float screenWidth=screensWidth[screenIndex];
                float screenHeight=screensHeight[screenIndex];
                #endif
                if(cam_id=="std_cam"){
                    #ifdef PLATFORM_3DS
                        setClipRectangle(0,0,screenWidth,screenHeight,screenWidth,screenHeight);
                    #endif
                    #ifdef PLATFORM_PSVITA
                        setClipRectangle(0,0,960,544,960,544);
                    #endif
                }else{
                    camera=GraphicsManager::getCamera(cam_id);
                    if(camera!=nullptr){
                         #ifdef PLATFORM_3DS
                            setClipRectangle(camera->getRx(), camera->getRy(), camera->getRx()+camera->getRw(), camera->getRy()+camera->getRh(), screenWidth, screenHeight);
                        #endif
                        #ifdef PLATFORM_PSVITA
                            setClipRectangle(camera->getRx(), camera->getRy(), camera->getRx()+camera->getRw(), camera->getRy()+camera->getRh(),960,544);
                        #endif
                    }
                }

                for(auto& [path, graphicOrders] : graphicOrdersDict){
                    std::sort(graphicOrders.begin(),graphicOrders.end(),[](const GraphicOrder& order1, const GraphicOrder& order2){
                        return order1.layer<order2.layer;
                    });
                    for(auto& graphicOrder : graphicOrders){
                        float x=graphicOrder.x;
                        float y=graphicOrder.y;
                        if(camera!=nullptr){
                            x-=(camera->getCx()-camera->getRx());
                            y-=(camera->getCy()-camera->getRy());
                        }
                        #ifdef PLATFORM_3DS
                        C2D_Image* baseImage=MemoryManager::getTexture(path);
                        if(baseImage!=nullptr){
                            float texWidth=baseImage->tex->width;
                            float texHeight=baseImage->tex->height;
                            bool coordsInRange=(
                                (graphicOrder.imageX >= 0 && graphicOrder.imageX + graphicOrder.imageWidth <= texWidth)
                                && (graphicOrder.imageY >= 0 && graphicOrder.imageY + graphicOrder.imageHeight <= texHeight)
                            );
                            if(coordsInRange){
                                Tex3DS_SubTexture tex={
                                    .width=static_cast<u_int16_t>(graphicOrder.imageWidth),
                                    .height=static_cast<u_int16_t>(graphicOrder.imageHeight),

                                    .left=graphicOrder.imageX/baseImage->tex->width,
                                    .top=(baseImage->tex->height - graphicOrder.imageY)/baseImage->tex->height,
                                    
                                    .right=(graphicOrder.imageX+graphicOrder.imageWidth)/baseImage->tex->width,
                                    .bottom=(baseImage->tex->height - (graphicOrder.imageY+graphicOrder.imageHeight))/baseImage->tex->height
                                };
                                C2D_Image modifiedImage=*baseImage;
                                modifiedImage.subtex=&tex;

                                C2D_ImageTint imageTint={
                                    .corners={
                                        {
                                            .color=C2D_Color32(255,255,255,graphicOrder.alpha),
                                            .blend=1.0f
                                        },
                                        {
                                            .color=C2D_Color32(255,255,255,graphicOrder.alpha),
                                            .blend=1.0f
                                        },
                                        {
                                            .color=C2D_Color32(255,255,255,graphicOrder.alpha),
                                            .blend=1.0f
                                        },
                                        {
                                            .color=C2D_Color32(255,255,255,graphicOrder.alpha),
                                            .blend=1.0f
                                        }
                                    }
                                };

                                C2D_DrawImageAt(modifiedImage,x,y,0,&imageTint,graphicOrder.scaleX,graphicOrder.scaleY);   
                            }else{
                                ErrorHandler::sendError(3,"coordinates out of range");
                            }
                        }
                        
                        #endif
                        
                        #ifdef PLATFORM_PSVITA
                        vita2d_texture* baseImage=MemoryManager::getTexture(path);
                        float texWidth=vita2d_texture_get_width(baseImage);
                        float texHeight=vita2d_texture_get_height(baseImage);
                        bool coordsInRange=(
                            (graphicOrder.imageX >= 0 && graphicOrder.imageX + graphicOrder.imageWidth <= texWidth)
                            && (graphicOrder.imageY >= 0 && graphicOrder.imageY + graphicOrder.imageHeight <= texHeight)
                        );
                        if(!coordsInRange){
                            ErrorHandler::sendError(3,"coordinates out of range");
                        }else{
                            if(baseImage!=nullptr)vita2d_draw_texture_tint_part_scale(
                                baseImage,
                                x,
                                y,
                                graphicOrder.imageX,
                                graphicOrder.imageY,
                                graphicOrder.imageWidth,
                                graphicOrder.imageHeight,
                                graphicOrder.scaleX,
                                graphicOrder.scaleY,
                                RGBA8(255,255,255,static_cast<int>(graphicOrder.alpha))
                            );
                        }
                        #endif
                    
                    }
                }
            }

            for(auto& [cam_id, textPipelineDict] : textPipeline[screenIndex]){
                Camera* camera=nullptr;
                #ifdef PLATFORM_3DS
                C2D_SceneBegin(screens[screenIndex]);
                float screensWidth[2]={400,320};
                float screensHeight[2]={240,240};
                float screenWidth=screensWidth[screenIndex];
                float screenHeight=screensHeight[screenIndex];
                #endif
                if(cam_id=="std_cam"){
                    #ifdef PLATFORM_3DS
                        setClipRectangle(0,0,screenWidth,screenHeight,screenWidth,screenHeight);
                    #endif
                    #ifdef PLATFORM_PSVITA
                        setClipRectangle(0,0,960,544,960,544);
                    #endif
                }else{
                    camera=GraphicsManager::getCamera(cam_id);
                    if(camera!=nullptr){
                         #ifdef PLATFORM_3DS
                            setClipRectangle(camera->getRx(), camera->getRy(), camera->getRx()+camera->getRw(), camera->getRy()+camera->getRh(), screenWidth, screenHeight);
                        #endif
                        #ifdef PLATFORM_PSVITA
                            setClipRectangle(camera->getRx(), camera->getRy(), camera->getRx()+camera->getRw(), camera->getRy()+camera->getRh(),960,544);
                        #endif
                    }
                }
                for(auto& textOrder : textPipelineDict){
                    float x=textOrder.x;
                    float y=textOrder.y;
                    if(camera!=nullptr){
                        x-=(camera->getCx()-camera->getRx());
                        y-=(camera->getCy()-camera->getRy());
                    }
                    for(auto& line : textOrder.lines){
                        #ifdef PLATFORM_3DS
                        textOrder.buf=C2D_TextBufNew(4096);
                        #endif

                        std::string displayedLine=line;
                        if(displayedLine.size()>=4000){
                            displayedLine=displayedLine.substr(0,4000);
                        }

                        #ifdef PLATFORM_3DS
                        C2D_TextFontParse(&textOrder.text,sysfont,textOrder.buf,displayedLine.c_str());
                        C2D_TextOptimize(&textOrder.text);

                        C2D_DrawText(&textOrder.text,C2D_WithColor,x,y,0,textOrder.scale/2,textOrder.scale/2,C2D_Color32(255,255,255,textOrder.alpha));
                        C2D_TextBufDelete(textOrder.buf);
                        #endif

                        #ifdef PLATFORM_PSVITA
                        
                        vita2d_pvf_draw_text(sysfont,x-1,y+13,RGBA8(255,255,255,static_cast<int>(textOrder.alpha)),textOrder.scale,line.c_str());

                        #endif
                        y+=textOrder.gap;
                    }
                }
            }
        
        texturePipeline[screenIndex]={};
        textPipeline[screenIndex]={};
    }
    #ifdef PLATFORM_PSVITA
    vita2d_disable_clipping();
    vita2d_end_drawing();
    sceDisplayWaitVblankStart();
    vita2d_swap_buffers();
    #endif
    #ifdef PLATFORM_3DS
    C3D_FrameEnd(0);
    #endif
}

void GraphicsManager::addCamera(std::string cam_id, float cx, float cy, float rx, float ry, float rw, float rh){
    cameras.emplace(cam_id, Camera(cx, cy, rx, ry, rw, rh));
}

void GraphicsManager::remCamera(std::string cam_id){
    if(cameras.find(cam_id)!=cameras.end()){
        cameras.erase(cam_id);
    }else{
        ErrorHandler::sendError(6,"camera "+cam_id+" is undefined");
    }
}

Camera* GraphicsManager::getCamera(std::string cam_id){
    auto camera=cameras.find(cam_id);
    if(camera!=cameras.end()){
        return &camera->second;
    }else{
        ErrorHandler::sendError(6,"camera "+cam_id+" is undefined");
        return nullptr;
    }
}