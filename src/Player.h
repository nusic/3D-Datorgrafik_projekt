#ifndef PLAYER_H
#define PLAYER_H

#include "Controller.h"
#include "DynamicGameObject.h"

class Player : public DynamicGameObject{
public:
    Player();
    ~Player();
    void updatePlayerOrientation(float dt);
    static int numberOfPlayers;

private:
	LightSource* lightSource;
    Controller* controller;
    int playerIndex;

};

#endif // PLAYER_H
