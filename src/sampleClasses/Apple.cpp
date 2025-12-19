#include "Apple.h"

Collider* Apple::getCollider(){
    return &collider;
}
void Apple::setCollider(Collider collider){
    this->collider=collider;
}