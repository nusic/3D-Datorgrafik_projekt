#include "Player.h"
#include <new>

int Player::numberOfPlayers = 0;

Player::Player():
GameObject(){
    speed = 15.0f;
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

void Player::updatePlayerOrientation(float dt, float * heightmap, int heightmapWidth, int heightmapHeight, float sceneWidth, float sceneHeight){
    controller->inputLoader();

    if(controller->validateLeftStickValues()){
        float xState = controller->getAxisValue(Controller::CONTROLLER_LEFT_X_AXIS)*dt*speed;
        float yState = controller->getAxisValue(Controller::CONTROLLER_LEFT_Y_AXIS)*dt*speed;

        //float s = 10.0f;

        int imgX = heightmapWidth/2  + heightmapWidth /sceneWidth * getPosition().x;
        int imgZ = heightmapHeight/2 + heightmapHeight/sceneHeight* getPosition().z;

        printf("imgX = %i  ", imgX);
        printf("imgZ = %i\n", imgZ);

        int XZPos = (int)(imgX + heightmapWidth*(heightmapHeight - imgZ));
        if(XZPos < 0){XZPos = 0;}
        //printf("XZpos = %i \n", XZPos);
        float zPosTemp = heightmap[XZPos] * 0.1f;
        //printf("position.z = %i    position.x = %i\n", (int) position.z, (int) position.x);
        printf("heightmap[%i] = %f\n", XZPos, zPosTemp);

        setYPosition(zPosTemp);
        setVelocity(xState, 0.0f, -yState);
        setDirection(180.0f / 3.141592f * glm::atan(xState,-yState));
        update(dt);
    }
    if (controller->validateRightStickValues()){
        float xState = controller->getAxisValue(Controller::CONTROLLER_RIGHT_X_AXIS);
        float yState = controller->getAxisValue(Controller::CONTROLLER_RIGHT_Y_AXIS);
        head.rotationNode->setRotation(180.0f / 3.141592 * glm::atan(xState,-yState), glm::vec3(0.0f,1.0f,0.0f));
    }

}
