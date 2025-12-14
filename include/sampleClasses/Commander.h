#ifndef COMMANDER_H
#define COMMANDER_H
#include "Node.h"

class Commander : public Node{
    private:
        Node* lastNode;
        bool gameOver;

    public:
        Commander(std::string imgId,int x,int y,std::vector<std::vector<int>> imageCoords,float imageCoordsIndex,float animationSpeed,std::vector<std::string> idsList,std::vector<std::string> scriptsIds):
            Node(imgId,x,y,imageCoords,imageCoordsIndex,animationSpeed,idsList,scriptsIds),
            lastNode(this),
            gameOver(false)
        {}
        void setLastNode(Node* lastNode);
        Node* getLastNode();

        void setGameOver(bool gameOver);
        bool getGameOver();
};
#endif