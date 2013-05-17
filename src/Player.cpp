#include "Player.h"

/*
    PLAYER
*/

int Player::numberOfPlayers = 0;

Player::Player():
GameObject("data/meshes/body.obj"){
    speed = 5.0f;
    controller = new Controller(numberOfPlayers);

    head = GameObject(0.0f, 5.0f, 0.0f);
    translationNode->addChildNode(head.getSceneGraphBranch());

    //int n = numberOfPlayers;
	//light->setColor(n/2, n%2, n/3);

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
/*
        sgct::MessageHandler::Instance()->print(
            "phi = %f, phiTarget = %f, phiDiff = %f", head.getPhi(), phiTarget, phiDiff);
        sgct::MessageHandler::Instance()->print("\r");
*/
    }
}

/*
    CHARACTER
*/

Character::Character():
Player(){
    animationIndex = 0;

    torch = GameObject("data/meshes/flashlight.obj");
    torch.setPosition(1.2f, -0.5f, 0.0f);
    torch.setAngleVel(3.0f);

    pickaxe = GameObject("data/meshes/flashlight.obj");
    pickaxe.setPosition(-1.2f, -0.5f, 0.0f);

    head.rotationNode->addChildNode(torch.getSceneGraphBranch());
    head.rotationNode->addChildNode(pickaxe.getSceneGraphBranch());

    light = new LightSource(torch.modelNode);
    light->setPosition(0,0,1.5f);
	light->setDirection(0,-1,4);

    light->setColor(0.9f, 0.8f, 0.7f);
    light->setIntensity(70);
    light->setSpread(30);
    torch.update(0.0f);
    pickaxe.update(0.0f);
}

Character::~Character(){

}

void Character::updateTorchDirection(){

}

void Character::updatePickaxeDirection(){

}

void Character::update(float dt){
    Player::update(dt);
    torch.rotationNode->setAxis(glm::vec3(1.0f, 0.0f, 0.0f));
    updateTorch();
    torch.update(dt);
//    pickaxe.update(dt);
}

void Character::updateTorch(){
    animationIndex++;

    if(animationIndex < 60){
        torch.setDirection(-animationIndex);
    }
    else{
        animationIndex = 0;
        torch.setDirection(-animationIndex);
    }
}


