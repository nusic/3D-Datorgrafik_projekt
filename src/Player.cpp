#include "Player.h"
#include <new>

Player::Player():
DynamicGameObject(){
    controller = new Controller();
	lightSource = new LightSource();

	lightSource->setDirection(10,2,10);
	lightSource->setColor(0.9,0.8,0.7);
    lightSource->setIntensity(70);
	lightSource->setSpread(10);

}
Player::~Player(){
    delete controller;
    //Väntar med att deletea lightSource då en del måsta fixas i den destruktorn
}
void Player::updatePlayerOrientation(){

    controller->inputLoader();
    if(controller -> validateLeftStickValues()){

        incrementPosition(
            0.1*controller->getAxisValue(Controller::CONTROLLER_LEFT_X_AXIS),
            0.1*controller->getAxisValue(Controller::CONTROLLER_LEFT_Y_AXIS));

        setDirection(180.0f/3.14159f * (float) glm::atan(
            controller->getAxisValue(Controller::CONTROLLER_LEFT_Y_AXIS),
            controller->getAxisValue(Controller::CONTROLLER_LEFT_X_AXIS)) + 90, 0.0f);
        
        lightSource->setPosition(position.x, position.z + 2, -position.y);
    }
    if (controller->validateRightStickValues()){

        glm::vec2 direction2d = glm::normalize(glm::vec2(
            -controller->getAxisValue(Controller::CONTROLLER_RIGHT_X_AXIS),
            controller->getAxisValue(Controller::CONTROLLER_RIGHT_Y_AXIS)));

        lightSource->setDirection(direction2d.x, 0.2, direction2d.y);
    }
    
    updateMatrix();
}
