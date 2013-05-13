#include "Player.h"
#include <new>

int Player::numberOfPlayers = 0;

Player::Player():
GameObject(){
    speed = 5.0f;
    controller = new Controller(numberOfPlayers);

    head = GameObject(0.0f, 2.0f, 0.0f);
    translationNode->addChildNode(head.getSceneGraphBranch());
    light = new LightSource(head.modelNode);
	light->setDirection(0,-1,4);
	light->setColor(0.9,0.8,0.7);
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

void Player::updatePlayerOrientation(float dt, float * heightmap, int heightmapWidth, int heightmapHeight, glm::vec3 sceneDimensions){
    controller->inputLoader();

    if(controller->validateLeftStickValues()){
        float xState = controller->getAxisValue(Controller::CONTROLLER_LEFT_X_AXIS);
        float yState = controller->getAxisValue(Controller::CONTROLLER_LEFT_Y_AXIS);

        int imgX = heightmapWidth/2  + heightmapWidth /sceneDimensions.x * (getPosition().x + xState);
        int imgY = heightmapHeight/2 - heightmapHeight/sceneDimensions.z * (getPosition().z + yState);

        int imgXYPos = (int)(imgX + heightmapWidth*imgY);

        float yTemp;
        if (0 < imgX && imgX < heightmapWidth &&
            0 < imgY && imgY < heightmapHeight)
            yTemp = heightmap[imgXYPos];
        else 
            yTemp = -0.0f;


        sgct::MessageHandler::Instance()->print(
          "position.x = %f  position.z = %f  imgX = %i  imgY = %i  heightmap[%i] = %f", 
           getPosition().x, getPosition().z, imgX,      imgY,                imgXYPos, yTemp);
        sgct::MessageHandler::Instance()->print("\r");

        float maxStep = 1.0f;
        if(yTemp - maxStep < getPosition().y){
            setVelocity(xState, 0.0f, -yState);
            setYPosition(yTemp);
        }
        else{
            setVelocity(0.0f, 0.0f, 0.0f);
        }
        setDirection(180.0f / 3.141592f * glm::atan(xState,-yState));
        update(dt);
    }
    if (controller->validateRightStickValues()){
        float xState = controller->getAxisValue(Controller::CONTROLLER_RIGHT_X_AXIS);
        float yState = controller->getAxisValue(Controller::CONTROLLER_RIGHT_Y_AXIS);
        head.rotationNode->setRotation(180.0f / 3.141592 * glm::atan(xState,-yState), glm::vec3(0.0f,1.0f,0.0f));
    }

}
