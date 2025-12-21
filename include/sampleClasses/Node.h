#ifndef NODE_H
#define NODE_H
#include "AnimatedImage.h"
struct SpeedVector{
    float x;
    float y;
};

class Node : public AnimatedImage{
    protected:
        std::vector<SpeedVector> positions;
        Node* follower;
        bool recordPositions;
        SpeedVector speedVector;
    public:
        Node(std::string imgId,int x,int y,std::vector<std::vector<float>> imageCoords,float imageCoordsIndex,float animationSpeed,float scaleX,float scaleY,std::vector<std::string> idsList,std::vector<std::string> scriptsIds):
            AnimatedImage(imgId,x,y,imageCoords,imageCoordsIndex,animationSpeed,scaleX,scaleY,idsList,scriptsIds),
            positions({}),
            follower(nullptr),
            recordPositions(true),
            speedVector({0,0})
        {}
        std::vector<SpeedVector>* getPositions();
        void setPositions(std::vector<SpeedVector> positions);

        Node* getFollower();
        void setFollower(Node* follower);

        bool getRecordPositions();
        void setRecordPositions(bool recordPositions);

        SpeedVector* getSpeedVector();
        void setSpeedVector(SpeedVector speedVector);

};
//"app0:/assets/spritesheet.png",0,0,{{10,5,18,18}},0,0,{},{"ctrl"}
#endif