#include "Player.h"
#include <new>

Player::Player():
DynamicGameObject(){
    controller = new Controller();
}
Player::~Player(){
    delete controller;
}
void Player::updatePlayerOrientation(){
    controller->inputLoader();
    if(controller -> validateLeftStickValues()){
        incrementPosition(0.1*controller->getAxisValue(CONTROLLER_LEFT_X_AXIS), 0.1*controller->getAxisValue(CONTROLLER_LEFT_Y_AXIS));
        setDirection(180.0f/3.14159f * (float) glm::atan(controller->getAxisValue(CONTROLLER_LEFT_Y_AXIS), controller->getAxisValue(CONTROLLER_LEFT_X_AXIS)) + 90, 0.0f);
    }
    updateMatrix();
}
