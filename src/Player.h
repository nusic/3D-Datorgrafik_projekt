#ifndef PLAYER_H
#define PLAYER_H

#include "Controller.h"
#include "GameObject.h"
#include "Transformation.h"

class Player : public GameObject{
public:
    Player();
    ~Player();

    void updatePlayerOrientation(
            float dt,
            float * heightmap,
            int heightmapWidth,
            int heightmapHeight,
            int heightmapArrayLength,
            glm::vec3 sceneDimensions);

    void updateUserInputs();
    void getLeftControllerValues(float &xState, float& yState) const;

    void updateHeadDirection(float dt);

    static int numberOfPlayers;

private:
	GameObject head;
	LightSource* light;

    Controller* controller;
    int playerIndex;

};

#endif // PLAYER_H
