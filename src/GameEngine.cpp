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

	//Creating the shader "SimpleColor"
	sgct::ShaderManager::Instance()->addShader("SimpleColor", "data/shaders/simple.vert", "data/shaders/simple.frag");
	if(!sgct::ShaderManager::Instance()->bindShader("SimpleColor"))
		std::cout << "ERROR: unable to bind shader!" << std::endl;

	glm::mat4 E(1.0f);
	glm::mat4 trans = glm::translate(E, glm::vec3(0.0f, 0.0f, 1.0f));

	Model* model = new Model(new ModelMesh("data/meshes/suzanne.obj"), trans, "SimpleColor");
	scene.push_back(*model);
	

	sgct::ShaderManager::Instance()->unBindShader();

}

void GameEngine::encode(){

}

void GameEngine::decode(){

}