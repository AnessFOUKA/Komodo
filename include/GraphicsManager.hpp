#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "MemoryManager.hpp"
#include "ErrorHandler.hpp"
#include "Camera.hpp"

#ifdef PLATFORM_3DS

#include <3ds.h>
#include <citro2d.h>

#endif

#ifdef PLATFORM_PSVITA

#include <vita2d.h>
#include <psp2/display.h>

#endif

struct GraphicOrder{
    float x;
    float y;
    float imageX;
    float imageY;
    float imageWidth;
    float imageHeight;
    float scaleX;
    float scaleY;
    float alpha;
    int layer;
    size_t screenIndex;
};

struct TextOrder{
    std::vector<std::string> lines;
    float x;
    float y;
    float gap;
    float scale;
    float alpha;
    #ifdef PLATFORM_3DS
    C2D_TextBuf buf;
    C2D_Text text;
    #endif
};

class GraphicsManager{
    static std::vector<std::unordered_map<std::string,std::unordered_map<std::string, std::vector<GraphicOrder>>>> texturePipeline;
    static std::vector<std::unordered_map<std::string,std::vector<TextOrder>>> textPipeline;
    static std::unordered_map<std::string, Camera> cameras;
    #ifdef PLATFORM_3DS
    static std::vector<C3D_RenderTarget*> screens;
    static C2D_Font sysfont;
    #endif
    #ifdef PLATFORM_PSVITA
    static vita2d_pvf* sysfont;
    #endif
    static void setClipRectangle(int x1, int y1, int x2, int y2, int screenWidth, int screenHeight);
    public:
        static void drawTexturePart(
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
            size_t screenIndex=0
        );
        static void drawText(std::vector<std::string> lines, float x, float y, float gap, float scale, float alpha, std::vector<std::string> cam_ids, size_t screenIndex);
        static void executeGraphicPipeline();
        static void addCamera(std::string cam_id, float cx, float cy, float rx, float ry, float rw, float rh);
        static void remCamera(std::string cam_id);
        static Camera* getCamera(std::string cam_id);
};

#endif