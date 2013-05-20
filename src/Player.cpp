#include "Player.h"

/*
    PLAYER
*/

int Player::numberOfPlayers = 0;

Player::Player():
GameObject("data/meshes/body.obj"){
    alive = true;
    speed = 10.0f;
    controller = new Controller(numberOfPlayers);
    
    playerRotationNode = new Rotation(0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    playerRotationNode->insertAfter(translationNode);

    head = GameObject(0.0f, 5.0f, 0.0f);
    playerRotationNode->addChildNode(head.getSceneGraphBranch());


    dyingLightTranslationNode = new Translation(translationNode, 0.0f, 0.0f, 0.0f);
    dyingLightRotationNode = new Rotation(dyingLightTranslationNode, 89.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    dyingLightSpeed = 3.0f;


    //int n = numberOfPlayers;
	//light->setColor(n/2, n%2, n/3);
    

    /*
    En player skapar en ScenGraphBranch som ser ut så här



        GameObject (body)
        ------------------
        |   Translation |
        |        |      |
        |        |                (for dying light)
        |        |------------------------
        |        |                       |
        |        |      |           Translation
        |        |      |                |
        |        |      |             Rotation
        |        |      |                |
        |        |      |          (Lightsource goes
        |        |      |           here when dying)
        |        |      |
        |        |      
        |        |  <- iserted playerRotationNode
        |        |
        |        |      |
        |        |
        |        |------------------------    GameObject (head)
        |        |               ------  |  ------
        |     Rotation  |        |   Translation |
        |        |      |        |       |       |
        |     Scaling   |        |    Rotation   |
        |        |      |        |       |       |
        |      Model    |        |    Scaling    |
        -----------------        |       |       |
                                 |     Model     |
                                 ------  |  ------
                                         |
                                    LightSource

    */
    numberOfPlayers++;
}

Player::~Player(){
    delete controller;
    //Väntar med att deletea lightSource då en del måsta fixas i den destruktorn
}

bool Player::isAlive() const{
    return alive;
}

void Player::update(float dt){
    if(alive){
        GameObject::update(dt);
        head.update(dt);
    }
    else{
        dyingLightPosition += dyingLightSpeed * dt;
        dyingLightTranslationNode->setTranslation(0.0f, dyingLightPosition, 0.0f);
    }
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

void Player::getRightControllerValues(float &xState, float& yState) const{
    if(controller->validateRightStickValues()){
        xState = controller->getAxisValue(Controller::CONTROLLER_RIGHT_X_AXIS);
        yState = controller->getAxisValue(Controller::CONTROLLER_RIGHT_Y_AXIS);
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

LightSource* Player::getLightSource() const{
    return NULL;
}

void Player::kill(){
    if(!alive)
        return;
    alive = false;
    playerRotationNode->setRotation(90.0f);
    setVelocity(0.0f, 0.0f, 0.0f);
    setAngleVel(0.0f);
    setDirection(0.0f);
    setYPosition(getPosition().y+1.0f);
    head.setVelocity(0.0f, 0.0f, 0.0f);
    head.setAngleVel(0.0f);
    head.setDirection(0.0f);
    update(0.0f);

    LightSource* light = getLightSource();
    light->removeFromParent();
    dyingLightRotationNode->addChildNode(light);
    dyingLightPosition = 6.0f;

    dyingLightRotationNode->addChildNode(new Model("data/meshes/suzanne.obj"));

}







//SUBCLASS OF PLAYER: CHARACTER

Character::Character():
Player(){
    animationIndex = 0;
    animationPickaxeIndex = 0;

    torch = GameObject("data/meshes/flashlight.obj");
    torch.setPosition(1.2f, -0.5f, 0.0f);
    torch.rotationNode->setAxis(glm::vec3(1.0f, 0.0f, 0.0f));

    pickaxe = GameObject("data/meshes/arm_pickaxe.obj");
    pickaxe.setPosition(-1.2f, -0.5f, 0.0f);
    pickaxe.rotationNode->setAxis(glm::vec3(1.0f, 0.0f, 0.0f));

    head.rotationNode->addChildNode(torch.getSceneGraphBranch());
    head.rotationNode->addChildNode(pickaxe.getSceneGraphBranch());

    light = new LightSource(torch.modelNode);
    light->setPosition(0,0,1.6f);
	light->setDirection(0,-0.2f,1);

    light->setColor(0.9f, 0.8f, 0.7f);
    light->setIntensity(256);
    light->setSpread(16);
    torch.update(0.0f);
    pickaxe.update(0.0f);
    
}

Character::~Character(){

}

LightSource* Character::getLightSource() const{
    return light;
}

void Character::update(float dt){
    Player::update(dt);
    //updateTorch();
    if(isAlive()){
        updatePickaxe();
        torch.update(dt);
        pickaxe.update(dt);
    }
}

void Character::updateTorchDirection(){

}

void Character::updatePickaxeDirection(){

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

void Character::updatePickaxe(){
    animationPickaxeIndex+=2;

    if(animationPickaxeIndex < 60){
        pickaxe.setDirection(-animationPickaxeIndex);
    }
    else{
        animationPickaxeIndex = -60;
        pickaxe.setDirection(-animationPickaxeIndex);
    }
}
