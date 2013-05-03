#include "GameEngine.h"

GameEngine::GameEngine(){

}

GameEngine::~GameEngine(){

}

void GameEngine::draw(){
	camera->incrementPosition();
	scene->drawScene(camera->getPerspectiveMatrix(), camera->getViewMatrix());
}

void GameEngine::preSync(){

}

void GameEngine::initOGL(){

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Enable blending -> render with alpha channel
	glEnable(GL_BLEND);

	// How to blend (?)
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Backface culling
	glEnable(GL_CULL_FACE);
	

	sgct::TextureManager::Instance()->loadTexure(
		"SimpleTexture", "data/textures/texture1.png", true);

	sgct::TextureManager::Instance()->loadTexure(
		"SimpleTexture2", "data/textures/texture2.png", true);

	//Creating the shader "SimpleColor"
	sgct::ShaderManager::Instance()->addShader(
		"SimpleColor", "data/shaders/simple.vert", "data/shaders/simple.frag");


	scene = new Scene();
	scene->initScene();

	camera = new Camera(-30, -5, 15);
	camera->setLookAt(0, 0, 0);
	camera->setVelocity(0.05, 0.02, -0.01);

	//Uncomment the two lines below to get simple static front view
	camera->setPosition(0, 15, 15);
	camera->setVelocity(0, 0, 0);
}

void GameEngine::encode(){

}

void GameEngine::decode(){

}

void GameEngine::keyCallback(int key, int action){

}

void GameEngine::mouseButtonCallback(int button, int action){

}
