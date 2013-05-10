#ifndef PLAYER_H
#define PLAYER_H

#include "Controller.h"
#include "DynamicGameObject.h"
#include "LightObject.h"
#include "Transformation.h"

class Player : public DynamicGameObject{
public:
    Player();
    ~Player();

    void updatePlayerOrientation(float dt);
    
    static int numberOfPlayers;

private:
	Translation* 	headPosition;
	Rotation* 		headRotation;
	Model*			headModel;
	LightSource* 	headLight;


    Controller* controller;
    int playerIndex;

};

#endif // PLAYER_H
