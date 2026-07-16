#ifndef KOMODO_H
#define KOMODO_H
#include <vita2d.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/display.h>
#include "MemoryManager.hpp"
class Komodo{
    private:
        static bool isRunning;
    public:
        static void gameloop();
        static void graphicPipeline();
};

#endif