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
    virtual LightSource* getLightSource() const;


    void kill();

    bool isAlive() const;


    static int numberOfPlayers;

    GameObject head;

protected:
    Rotation* playerRotationNode;

private:
    bool alive;

    Controller* controller;
    int playerIndex;

};




//SUBCLASS OF PLAYER: CHARACTER

class Character : public Player{
public:
    Character();
    ~Character();

    virtual void update(float dt);
    virtual LightSource* getLightSource() const;


private:
    void updateTorch();
    void updateTorchDirection();
    void updatePickaxeDirection();


    GameObject torch;
    GameObject pickaxe;

    LightSource* light;

    int animationIndex;
};

#endif // PLAYER_H
