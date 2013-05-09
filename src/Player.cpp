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
	head->light->setSpread(30);

    //children.push_back(head);

    numberOfPlayers++;
}

Player::~Player(){
    delete controller;
    //Väntar med att deletea lightSource då en del måsta fixas i den destruktorn
}

void Player::updatePlayerOrientation(float dt){
    controller->inputLoader();

    if(controller->validateLeftStickValues()){
        float xState = controller->getAxisValue(Controller::CONTROLLER_LEFT_X_AXIS)*dt*speed;
        float yState = controller->getAxisValue(Controller::CONTROLLER_LEFT_Y_AXIS)*dt*speed;
        incrementPositionAndTurnTo(xState,0.0f,-yState);
        head->setPosition(position.x, position.y + 2.0f, position.z);
    }
    if (controller->validateRightStickValues()){
        float xState = controller->getAxisValue(Controller::CONTROLLER_RIGHT_X_AXIS);
        float yState = controller->getAxisValue(Controller::CONTROLLER_RIGHT_Y_AXIS);
        glm::vec2 direction2d = glm::normalize(glm::vec2(xState,yState));
        head->setDirection(direction2d.x, -0.2f, -direction2d.y, phi);
    }
    //head->updateMatrix();
    updateMatrix();
    //head->updateLightOrientation(modelMatrix);

}
