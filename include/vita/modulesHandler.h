#ifndef MODULESHANDLER_H
#define MODULESHANDLER_H
#include <psp2/ctrl.h>
#include <psp2/display.h>
#include <psp2/kernel/processmgr.h>
#include <vita2d.h>
#include <functional>
#include <vector>
#include <map>
#include <iostream>
#include <string.h>
#include <chrono>
#include <memory>
class GameObject;
class Camera;
class Game;
bool detectInbound(int x1,int y1,int width1,int heigth1,int x2,int y2,int width2,int heigth2);
#endif