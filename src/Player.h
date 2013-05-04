#ifndef PLAYER_H
#define PLAYER_H

#include "Controller.h"
#include "DynamicGameObject.h"
#include "LightObject.h"

class Player : public DynamicGameObject{
public:
    Player();
    ~Player();
    void updatePlayerOrientation();

    static int numberOfPlayers;

private:
	LightObject* head;
    Controller* controller;


};

#endif // PLAYER_H
