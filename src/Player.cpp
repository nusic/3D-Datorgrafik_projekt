#include "Player.h"
#include <new>

int Player::numberOfPlayers = 0;

Player::Player():
DynamicGameObject(){

    controller = new Controller(numberOfPlayers);

    headPosition = new Translation(getSceneGraphBranch(), 0.0f, 2.0f, 0.0f);
    headRotation = new Rotation(headPosition, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    headModel = new Model(headRotation, new ModelMesh("data/meshes/suzanne.obj"), "SimpleTexture2", "SimpleColor");
    headLight = new LightSource(headModel);

	headLight->setDirection(0,-1,4);
	headLight->setColor(0.9,0.8,0.7);
    headLight->setIntensity(70);
	headLight->setSpread(30);

    numberOfPlayers++;



    /*
    En player skapar en ScenGraphBranch som ser ut så här

            Translation
                 |
                 |---------------
                 |              |
              Rotation      Translation
                 |              |
              Scaling        Rotation
                 |              |
               Model         Scaling
                                |
                              Model
                                |
                            LightSource

    */
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
        //head->setPosition(position.x, position.y + 2.0f, position.z);
    }
    if (controller->validateRightStickValues()){
        float xState = controller->getAxisValue(Controller::CONTROLLER_RIGHT_X_AXIS);
        float yState = controller->getAxisValue(Controller::CONTROLLER_RIGHT_Y_AXIS);
        glm::vec2 direction2d = glm::normalize(glm::vec2(xState,yState));
        headRotation->setRotation(180.0f / 3.141592 * glm::atan(xState,-yState), glm::vec3(0.0f,1.0f,0.0f));
        //head->setDirection(direction2d.x, -0.2f, -direction2d.y, phi);
    }
    //head->updateMatrix();
    updateMatrix();
    //head->updateLightOrientation(modelMatrix);

}
