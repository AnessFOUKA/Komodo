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
#include <cmath>
class GameObject;
class Camera;
class Game;
bool detectInbound(float x1,float y1,float width1,float heigth1,float x2,float y2,float width2,float heigth2);
#endif