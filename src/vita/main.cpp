#include <iostream>
#include "Komodo.hpp"
int main(){
    MemoryManager::storeData("app0:/assets/test.png",TEXTURE);
    MemoryManager::removeData("app0:/assets/test.png",TEXTURE);
    Komodo::gameloop();
    return 0;
}