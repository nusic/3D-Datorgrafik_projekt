#ifndef PLAYER_H
#define PLAYER_H

#include "Controller.h"
#include "GameObject.h"

class Player : public GameObject{
public:
    Player();
    ~Player();
    void updatePlayerOrientation();

private:
    Controller* controller;
    static const int CONTROLLER_LEFT_X_AXIS = 0;
    static const int CONTROLLER_LEFT_Y_AXIS = 1;
    static const int CONTROLLER_RIGHT_X_AXIS = 3;
    static const int CONTROLLER_RIGHT_Y_AXIS = 4;
};

#endif // PLAYER_H
