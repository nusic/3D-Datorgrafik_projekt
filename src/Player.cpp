#include "Player.h"
#include <new>

int Player::numberOfPlayers = 0;

Player::Player():
DynamicGameObject(){
    controller = new Controller(numberOfPlayers);

    head = new LightObject(0, 2, 0);
    head->light = new LightSource();
	head->light->setDirection(10,2,10);
	head->light->setColor(0.9,0.8,0.7);
    head->light->setIntensity(70);
	head->light->setSpread(10);

    children.push_back(head);

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

        head->setPosition(position.x, position.y + 2, position.z);
    }
    if (controller->validateRightStickValues()){

        glm::vec2 direction2d = glm::normalize(glm::vec2(
            controller->getAxisValue(Controller::CONTROLLER_RIGHT_X_AXIS),
            controller->getAxisValue(Controller::CONTROLLER_RIGHT_Y_AXIS)));

        head->setDirection(direction2d.x, -0.2, -direction2d.y, phi);
    }
    head->updateMatrix();
    updateMatrix();
    //head->updateLightOrientation(modelMatrix);

}
