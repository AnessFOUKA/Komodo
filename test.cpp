#include <pthread.h>
#include <iostream>

void* afficher(void* message){
    std::string* val=static_cast<std::string*>(message);
    for(int i=0; i<5; i++){
        std::cout<<*val<<std::endl;
    }

    *val="eeee";

    return nullptr;
}

int main(){
    pthread_t thread;
    std::string value="aaaa";

    pthread_create(&thread,nullptr,afficher,&value);
    pthread_join(thread,nullptr);
    std::cout<<value<<std::endl;
}