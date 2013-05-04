#include "Player.h"
#include <new>

int Player::numberOfPlayers = 0;

Player::Player():
DynamicGameObject(){
    controller = new Controller(numberOfPlayers);
	lightSource = new LightSource();
	lightSource->setDirection(10,2,10);
	lightSource->setColor(0.9,0.8,0.7);
    lightSource->setIntensity(70);
	lightSource->setSpread(10);
    numberOfPlayers++;
}

Player::~Player(){
    delete controller;
    //Väntar med att deletea lightSource då en del måsta fixas i den destruktorn
}

void Player::updatePlayerOrientation(){
    controller->inputLoader();
    if(controller -> validateLeftStickValues()){

        incrementPositionAndTurnTo(
            0.1*controller->getAxisValue(Controller::CONTROLLER_LEFT_X_AXIS),
            0,
            -0.1*controller->getAxisValue(Controller::CONTROLLER_LEFT_Y_AXIS));

        lightSource->setPosition(position.x, position.y + 2, position.z);
    }
    if (controller->validateRightStickValues()){

        glm::vec2 direction2d = glm::normalize(glm::vec2(
            controller->getAxisValue(Controller::CONTROLLER_RIGHT_X_AXIS),
            controller->getAxisValue(Controller::CONTROLLER_RIGHT_Y_AXIS)));

        lightSource->setDirection(direction2d.x, -0.2, -direction2d.y);
    }

    updateMatrix();
}
