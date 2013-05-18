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
    void getRightControllerValues(float &xState, float& yState) const;

    void updateHeadDirection();
    virtual void update(float dt);

    static int numberOfPlayers;

    GameObject head;

private:
    Controller* controller;
    int playerIndex;

};

class Character : public Player{
public:
    Character();
    ~Character();

    void update(float dt);
    void updateTorch();

    void updateTorchDirection();
    void updatePickaxeDirection();

private:
    GameObject torch;
    GameObject pickaxe;

    LightSource* light;

    int animationIndex;
};

#endif // PLAYER_H
