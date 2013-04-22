#include "GameEngine.h"

GameEngine::GameEngine(){

}

GameEngine::~GameEngine(){
	
}


void GameEngine::draw(){
	std::cout << "draw Checkpoint 1" << std::endl;
	glm::mat4 ViewPerspective(1.0f);
	scene->drawScene(ViewPerspective);
	std::cout << "draw DONE" << std::endl;
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

	//Creating the shader "SimpleColor"
	sgct::ShaderManager::Instance()->addShader("SimpleColor", "data/shaders/simple.vert", "data/shaders/simple.frag");
	if(!sgct::ShaderManager::Instance()->bindShader("SimpleColor"))
		std::cout << "ERROR: unable to bind shader!" << std::endl;
	
	scene = new Scene();
	std::cout << "Checkpoint 1" << std::endl;
	scene->initScene();
	std::cout << "Checkpoint 2" << std::endl;
	sgct::ShaderManager::Instance()->unBindShader();

	std::cout << "Checkpoint 3" << std::endl;

}

void GameEngine::encode(){

}

void GameEngine::decode(){

}