#ifndef PLAYER_H
#define PLAYER_H

#include <math.h>
#include <new>

#include "Controller.h"
#include "GameObject.h"
#include "Transformation.h"


class Player : public GameObject{
public:
    Player();
    ~Player();

    void updateUserInputs();
    void getLeftControllerValues(float &xState, float& yState) const;


    void updateHeadDirection();
    void update(float dt);

    static int numberOfPlayers;

private:
	GameObject head;
	LightSource* light;

    Controller* controller;
    int playerIndex;

};

#endif // PLAYER_H
