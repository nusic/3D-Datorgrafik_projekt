#ifndef PLAYER_H
#define PLAYER_H

#include "Controller.h"
#include "DynamicGameObject.h"

class Player : public DynamicGameObject{
public:
    Player();
    ~Player();
    void updatePlayerOrientation();

    bool arrowButtons[4];
    enum directions {FORWARD = 0, BACKWARD, LEFT, RIGHT};

private:
	LightSource* lightSource;
    Controller* controller;
};

#endif // PLAYER_H
