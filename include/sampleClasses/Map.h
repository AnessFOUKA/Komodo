#ifndef MAP_H
#define MAP_H
#include "ItemHandler.h"
class Map : public ItemHandler{
    int score;
    public:
        Map(std::vector<std::string> idsList,std::vector<std::string> scriptsIds):
            ItemHandler(idsList,scriptsIds),
            score(0)
        {}
        int getScore();
        void setScore(int score);
};
#endif