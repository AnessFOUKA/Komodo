#ifndef ERRORHANDLER
#define ERRORHANDLER
#include "InputManager.h"

struct Error{
    int type;
    std::string message;
    bool showErrorScreen;
    bool saveToLogs;
};

class ErrorHandler{
    private:
        std::vector<Error> errorStack;
        std::string logFilePath; 
        std::string logSavingError;
        int errorStackCursor;
        bool showErrorScreen;
        vita2d_pvf** pvf;
        InputManager* inputManager;
        bool allowErrorScreens;
    public:
        ErrorHandler(vita2d_pvf** pvf,InputManager* inputManager);
        void setLogFilePath(std::string logFilePath);
        std::string getLogFilePath();
        void manageErrors();
        bool getShowErrorScreen();
        bool getAllowErrorScreens();
        void setAllowErrorScreens(bool allowErrorScreens);
        void sendError(int type,std::string message,bool showErrorScreen,bool saveToLogs);

};
#endif