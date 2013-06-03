#ifndef PLAYER_H
#define PLAYER_H

#include <math.h>
#include <new>

#include "Controller.h"
#include "GameObject.h"
#include "StaticGameObject.h"
#include "Transformation.h"


class Player : public GameObject{
public:
    Player();
    ~Player();

    void updateUserInputs();
    void getLeftControllerValues(float &xState, float& yState) const;
    void getRightControllerValues(float &xState, float& yState) const;

    const Controller * const getController() const;

    void updateHeadDirection();

    virtual void update(float dt);


    void kill();
    void revive();
    bool isAlive() const;
    void toggleLight();

    void startAttackAnimation();


    static int numberOfPlayers;

    GameObject head;

protected:
    Rotation* playerRotationNode;

    LightSource* light;
    float originalLightIntensity;
    Node* originalLightParent;

    Translation* dyingLightTranslationNode;
    Rotation* dyingLightRotationNode;
    float dyingLightSpeed;
    float dyingLightPosition;
    float originalDyingLightPosition;


    bool animatingAttack;
    int attackAnimationIndex;


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


private:
    void updateTorch();
    void updatePickaxe();


    GameObject leftArm;
    GameObject rightArm;

    

    int animationIndex;

    
    static float pickaxeAnimationValues[];
    static const int ATTACK_ANIMATION_LENGTH = 20;
};

#endif // PLAYER_H
