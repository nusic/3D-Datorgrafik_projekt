#include "Player.h"

/*
    PLAYER
*/

int Player::numberOfPlayers = 0;

Player::Player():
GameObject("ghost_body", "ghost_body_texture"){
    alive = true;
    speed = 10.0f;
    attackAnimationIndex = 0;
    animatingAttack = false;

    controller = new Controller(numberOfPlayers, this);

    playerRotationNode = new Rotation(0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    playerRotationNode->insertAfter(translationNode);

    head = GameObject("ghost_head", "ghost_head_texture");
    head.setPosition(0.0f, 2.2f, 0.0f);
    head.update(0.0f);
    playerRotationNode->addChildNode(head.getSceneGraphBranch());


    dyingLightTranslationNode = new Translation(translationNode, 0.0f, 0.0f, 0.0f);
    dyingLightRotationNode = new Rotation(dyingLightTranslationNode, 89.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    dyingLightSpeed = 3.0f;
    originalDyingLightPosition = 1.0f;
    originalLightIntensity = 170.0f;


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

const Controller * const Player::getController() const{
    return controller;
}

void Player::update(float dt){
    if(alive){
        
        float yTeabag = controller->getAxisValue(Controller::CONTROLLER_RT);
        setYPosition(getPosition().y + 1.7f + 0.7 * glm::sin(4 * sgct::Engine::getTime()));
        setYPosition(getPosition().y + yTeabag);

        GameObject::update(dt);
        head.update(dt);
    }
    else{
        dyingLightPosition += dyingLightSpeed * dt;
        dyingLightTranslationNode->setTranslation(0.0f, dyingLightPosition, 0.0f);
        //light->setIntensity(originalLightIntensity*originalDyingLightPosition/dyingLightPosition);
    }
    light->update();
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

void Player::startAttackAnimation(){
    animatingAttack = true;
    attackAnimationIndex = 0;
}

void Player::kill(){
    if(!alive)
        return;
    alive = false;
    playerRotationNode->setRotation(90.0f);
    setVelocity(0.0f, 0.0f, 0.0f);
    setAngleVel(0.0f);
    setDirection(0.0f);
    setYPosition(getPosition().y-1.0f);
    head.setVelocity(0.0f, 0.0f, 0.0f);
    head.setAngleVel(0.0f);
    head.setDirection(0.0f);

    originalLightParent = light->getParentNode();
    light->removeFromParent();

    Translation* lightTranslationNode = new Translation(dyingLightRotationNode, 0.0f, 0.0f, -1.0f);

    lightTranslationNode->addChildNode(light);
    light->setIntensity(originalLightIntensity/2);
    dyingLightPosition = originalDyingLightPosition;
    //Model* cross = new Model("cross", "cross_texture");
    
    Rotation* rotationNode = new Rotation(dyingLightRotationNode, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    //rotationNode->addChildNode(cross);

    update(0.0f);
}

void Player::revive(){
    if(alive)
        return;
    alive = true;
    playerRotationNode->setRotation(0.0f);

    light->removeFromParent();
    light->setIntensity(originalLightIntensity);
    originalLightParent->addChildNode(light);
    //Node * soul = dyingLightRotationNode->getChildByName("cross");
    //dyingLightRotationNode->removeChildNode(soul);

    update(0.0f);
}

void Player::toggleLight(){
    light->setIntensity( (light->getIntensity() == 0) ? originalLightIntensity : 0.0f );
}





//SUBCLASS OF PLAYER: CHARACTER

Character::Character():
Player(){
    animationIndex = 0;
    

    leftArm = GameObject("ghost_arm_left", "ghost_arm_right_texture");
    leftArm.setPosition(1.2f, -0.5f, 0.0f);
    leftArm.rotationNode->setAxis(glm::vec3(1.0f, 0.0f, 0.0f));
    leftArm.setDirection(10.0f);

    StaticGameObject flashLight("flash_light", "flash_light_texture");
    flashLight.setPosition(0.8f, -0.7f, 1.8f);
    leftArm.rotationNode->addChildNode(flashLight.getSceneGraphBranch());

    rightArm = GameObject("ghost_arm_right", "ghost_arm_right_texture");
    rightArm.setPosition(-1.2f, -0.5f, 0.0f);
    rightArm.rotationNode->setAxis(glm::vec3(1.0f, 0.0f, 0.0f));

    StaticGameObject pickAxe("pick_axe", "pick_axe_texture");
    pickAxe.setPosition(-0.6f, 0.0f, 1.8f);
    pickAxe.setRotation(0.0f, 20.0f);
    rightArm.rotationNode->addChildNode(pickAxe.getSceneGraphBranch());

    head.rotationNode->addChildNode(leftArm.getSceneGraphBranch());
    head.rotationNode->addChildNode(rightArm.getSceneGraphBranch());

    light = new LightSource(flashLight.modelNode);
    light->setPosition(0,0,1.0f);
	//light->setDirection(0,-0.2f,1);

    light->setColor(0.9f, 0.8f, 0.7f);
    light->setIntensity(170);

    light->setSpread(32);
    leftArm.update(0.0f);
    rightArm.update(0.0f);
    //pickAxe.update(0.0f);

}

float Character::pickaxeAnimationValues[] = {-60.0f, -50.0f, -35.0f, -15.0f, 10.0f, 40.0f, 35.0f, 30.0f, 20.0f, 10.0f, 0.0f, -10.0f, -20.0f, -30.0f, -35.0f, -40.0f, -45.0f, -50.0f, -55.0f, -60.0f};

Character::~Character(){

}

void Character::update(float dt){
    Player::update(dt);
    if(isAlive()){
        //updateleftArm();
        updatePickaxe();
        leftArm.update(dt);
        rightArm.update(dt);
    }
}


void Character::updatePickaxe(){
    if(animatingAttack){

        if(attackAnimationIndex < ATTACK_ANIMATION_LENGTH){
            rightArm.setDirection(pickaxeAnimationValues[attackAnimationIndex]);
            ++attackAnimationIndex;
        }
        else{
            animatingAttack = false;
        }
    }
}

/*
void Character::updateleftArm(){
    animationIndex++;

    if(animationIndex < 60){
        leftArm.setDirection(-animationIndex);
    }
    else{
        animationIndex = 0;
        leftArm.setDirection(-animationIndex);
    }
}
*/
