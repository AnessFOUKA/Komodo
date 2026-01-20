#ifndef COMMANDER_H
#define COMMANDER_H
#include "Node.h"

class Commander : public Node{
    private:
        Node* lastNode;
        bool gameOver;
        Collider collider;

    public:
        Commander(std::string imgId,int x,int y,std::vector<ImageCoord> imageCoords,float imageCoordsIndex,float animationSpeed,float scaleX,float scaleY,std::vector<std::string> idsList,std::vector<std::string> scriptsIds):
            Node(imgId,x,y,imageCoords,imageCoordsIndex,animationSpeed,scaleX,scaleY,idsList,scriptsIds),
            lastNode(this),
            gameOver(false),
            collider(x,y,width,height)
        {}
        void setLastNode(Node* lastNode);
        Node* getLastNode();

        void setGameOver(bool gameOver);
        bool getGameOver();

        Collider* getCollider();
        void setCollider(Collider collider);
};
#endif