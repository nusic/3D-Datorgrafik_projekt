#include "Player.h"
#include <new>

Player::Player(){
    std::cout << "Player konstrukeorf CHECKPOINT 1" << std::endl;
    controller = new Controller();
    if(!controller)
        std::cout << "JÄVLAR VAD FEL DET BLEV" << std::endl;
    std::cout << "Player konstrukeorf CHECKPOINT 2" << std::endl;
}

Player::~Player(){
    //dtor
}

void Player::updatePlayerOrientation(){
    controller->inputLoader();
    setPosition(1*controller->getAxes(CONTROLLER_LEFT_X_AXIS), 1*controller->getAxes(CONTROLLER_LEFT_Y_AXIS));
    setDirection(180.0f/3.14159f * (float) glm::atan(controller->getAxes(CONTROLLER_RIGHT_Y_AXIS), controller->getAxes(CONTROLLER_RIGHT_X_AXIS)), 0.0f);
    updateMatrix();
}
