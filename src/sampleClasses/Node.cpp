#include "Node.h"
std::vector<SpeedVector>* Node::getPositions(){
    return &positions;
}
void Node::setPositions(std::vector<SpeedVector> positions){
    this->positions=positions;
}

Node* Node::getFollower(){
    return follower;
}

void Node::setFollower(Node* follower){
    this->follower=follower;
}

bool Node::getRecordPositions(){
    return recordPositions;
}

void Node::setRecordPositions(bool recordPositions){
    this->recordPositions=recordPositions;
}

SpeedVector* Node::getSpeedVector(){
    return &speedVector;
}
        
void Node::setSpeedVector(SpeedVector speedVector){
    this->speedVector=speedVector;
}