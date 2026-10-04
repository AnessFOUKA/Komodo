#ifndef CAMERA_H
#define CAMERA_H

#include <vector>

class Camera{
    
    float cx;
    float cy;
    float rx;
    float ry;
    float rw;
    float rh;

    public:
        
        Camera(float cx, float cy, float rx, float ry, float rw, float rh):
            cx(cx),
            cy(cy),
            rx(rx),
            ry(ry),
            rw(rw),
            rh(rh)
        {}
    
        float getCx();
        float getCy();
        float getRx();
        float getRy();
        float getRw();
        float getRh();

        void setCx(float cx);
        void setCy(float cy);
        void setRx(float rx);
        void setRy(float ry);
        void setRw(float rw);
        void setRh(float rh);

};

#endif