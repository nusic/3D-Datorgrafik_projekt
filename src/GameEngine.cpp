#include "GameEngine.h"
#include "sgct.h"

GameEngine::GameEngine(){

}

GameEngine::~GameEngine(){

}

void GameEngine::drawScene(){

	for (int i = 0; i < scene.size(); ++i){
		glm::mat4 MVP;
		scene[i].drawModel(MVP);
	}

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



}

void GameEngine::encode(){

}

void GameEngine::decode(){

}