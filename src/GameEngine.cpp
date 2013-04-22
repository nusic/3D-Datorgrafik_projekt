#include "GameEngine.h"
#include "sgct.h"

GameEngine::GameEngine(){

}

GameEngine::~GameEngine(){

}

double y = 0.0;
void GameEngine::drawScene(){
	y += 0.001;
	for (int i = 0; i < scene.size(); ++i){
		scene[i].setPosition(0, y);
		scene[i].setDirection(1000.0f*y, 0.0f);
		scene[i].updateMatrix();
		glm::mat4 VP;
		scene[i].drawModel(VP);
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

	//Creating the shader "SimpleColor"
	sgct::ShaderManager::Instance()->addShader("SimpleColor", "data/shaders/simple.vert", "data/shaders/simple.frag");
	if(!sgct::ShaderManager::Instance()->bindShader("SimpleColor"))
		std::cout << "ERROR: unable to bind shader!" << std::endl;

	glm::mat4 E(1.0f);
	float s = 0.3f;
	glm::mat4 scale = glm::scale(E, glm::vec3(s,s,s));
	glm::mat4 trans = glm::translate(scale, glm::vec3(0.0f, 0.0f, 1.0f));
	

	GameObject* object = new GameObject(0.5,0.1,0.5);
	scene.push_back(*object);
	

	sgct::ShaderManager::Instance()->unBindShader();

}

void GameEngine::encode(){

}

void GameEngine::decode(){

}