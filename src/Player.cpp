#include "Player.h"


int Player::numberOfPlayers = 0;

Player::Player():
GameObject(){
    speed = 5.0f;
    controller = new Controller(numberOfPlayers);

    head = GameObject(0.0f, 2.0f, 0.0f);
    translationNode->addChildNode(head.getSceneGraphBranch());
    light = new LightSource(head.modelNode);
	light->setDirection(0,-1,4);

    //int n = numberOfPlayers;
	//light->setColor(n/2, n%2, n/3);
    light->setColor(0.9f, 0.8f, 0.7f);
    light->setIntensity(70);
	light->setSpread(30);

    numberOfPlayers++;



    /*
    En player skapar en ScenGraphBranch som ser ut så här



        GameObject (body)
        ------------------
        |   Translation  |
        |         |      
        |         |------------------------    GameObject (head)
        |         |               ------  |  ------ 
        |      Rotation  |        |   Translation |
        |         |      |        |       |       |
        |      Scaling   |        |   Rotation    |
        |         |      |        |       |       |
        |       Model    |        |   Scaling     |
        ------------------        |       |       |     
                                  |     Model     |
                                  ------  |  ------
                                          | 
                                     LightSource

    */
}

Player::~Player(){
    delete controller;
    //Väntar med att deletea lightSource då en del måsta fixas i den destruktorn
}

void Player::update(float dt){
    GameObject::update(dt);
    head.update(dt);
}

void Player::updateUserInputs(){
    controller->inputLoader();
}

void Player::getLeftControllerValues(float &xState, float& yState) const{
    if(controller->validateLeftStickValues()){
        xState = controller->getAxisValue(Controller::CONTROLLER_LEFT_X_AXIS);
        yState = controller->getAxisValue(Controller::CONTROLLER_LEFT_Y_AXIS);
    }
}

void Player::updateHeadDirection(){
    if (controller->validateRightStickValues()){
        float xState = controller->getAxisValue(Controller::CONTROLLER_RIGHT_X_AXIS);
        float yState = controller->getAxisValue(Controller::CONTROLLER_RIGHT_Y_AXIS);
        float phiTarget = 180.0f / 3.141592 * glm::atan(xState,-yState);
        float phiDiff = fmod(phiTarget - head.getPhi() + 3*180.0f, 360.0f) - 180.0f;
        head.setAngleVel(phiDiff);

        sgct::MessageHandler::Instance()->print(
            "phi = %f, phiTarget = %f, phiDiff = %f", head.getPhi(), phiTarget, phiDiff);
        sgct::MessageHandler::Instance()->print("\r");
    
    }
}

