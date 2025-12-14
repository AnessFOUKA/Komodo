#include "Commander.h"
void Commander::setLastNode(Node* lastNode){
    this->lastNode=lastNode;
}

Node* Commander::getLastNode(){
    return lastNode;
}

void Commander::setGameOver(bool gameOver){
    this->gameOver=gameOver;
}

bool Commander::getGameOver(){
    return gameOver;
}