#include "Player.h"
#include <new>

Player::Player(){
    controller = new Controller();
}

Player::~Player(){
    delete controller;
}

void Player::updatePlayerOrientation(){
    controller->inputLoader();
    incrementPosition(1*controller->getAxes(CONTROLLER_LEFT_X_AXIS), 1*controller->getAxes(CONTROLLER_LEFT_Y_AXIS));
    setDirection(180.0f/3.14159f * (float) glm::atan(controller->getAxes(CONTROLLER_LEFT_Y_AXIS), controller->getAxes(CONTROLLER_LEFT_X_AXIS)) + 90, 0.0f);
    updateMatrix();
}
