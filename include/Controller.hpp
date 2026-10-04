#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <unordered_map>
#include <vector>
#include <string>

class Controller{

    protected:
    
        std::unordered_map<std::string, std::vector<float>> keysState;
        std::unordered_map<std::string, std::vector<float>> downKeys;
        std::unordered_map<std::string, std::vector<float>> keysFormerState;

    public:
    
        Controller():
            keysState(),
            keysFormerState()
        {}
        
        ~Controller()=default;

        virtual void updateKeysState()=0;
        virtual std::unordered_map<std::string, std::vector<float>>* getKeysState();
        virtual std::unordered_map<std::string, std::vector<float>>* getDownKeys();
        virtual std::unordered_map<std::string, std::vector<float>>* getKeysFormerState();
};

#endif