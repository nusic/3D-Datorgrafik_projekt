#include "GameEngine.h"

GameEngine::GameEngine(){

}

GameEngine::~GameEngine(){

}

void GameEngine::draw(){
    player->updatePlayerOrientation();
	camera->incrementPosition();
	scene->drawScene(camera->getViewPerspectiveMatrix());
	player->drawModel(camera->getViewPerspectiveMatrix());
}

void GameEngine::preSync(){

}

void GameEngine::initOGL(){

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	sgct::TextureManager::Instance()->loadTexure("SimpleTexture", "data/textures/texture1.png", true);

	//Creating the shader "SimpleColor"
	sgct::ShaderManager::Instance()->addShader("SimpleColor", "data/shaders/simple.vert", "data/shaders/simple.frag");
	if(!sgct::ShaderManager::Instance()->bindShader("SimpleColor"))
		std::cout << "ERROR: unable to bind shader!" << std::endl;

	scene = new Scene();
	scene->initScene();
	sgct::ShaderManager::Instance()->unBindShader();


	camera = new Camera(-30, -5, 15);
	camera->setLookAt(0, 0, 0);
	camera->setVelocity(0.05, 0.02, -0.01);

	//Uncomment the two lines below to get simple static front view
	camera->setPosition(0, 15, 15);
	camera->setVelocity(0, 0, 0);


    player = new Player;
    player->setPosition(0.0f, 0.0f);


}

void GameEngine::encode(){

}

void GameEngine::decode(){

}
