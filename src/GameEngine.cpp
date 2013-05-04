#include "GameEngine.h"

GameEngine::GameEngine(){

}

GameEngine::~GameEngine(){

}

void GameEngine::draw(){
	sgct::ShaderManager::Instance()->bindShader( "SimpleColor" );
	glUniform1f(currentTimeId, static_cast<float>(currentTime));
	glUniform1f(globalRandomId, static_cast<float>(globalRandom));
	sgct::ShaderManager::Instance()->unBindShader();

	scene->drawScene(camera->getPerspectiveMatrix(), camera->getViewMatrix());
}

void GameEngine::preSync(){
	currentTime = sgct::Engine::getTime();

	//gör så att vår stokastiska variabel "globalRandom" får en
	//kankse lite roligare fördelningsfunktions mha en sinus.
	//Ska likna brinnande eld var tanken dårå.
	globalRandom = sin(0.3f+rand()/(float)RAND_MAX);

	camera->incrementPosition();
	camera->calcMatrices();

	for (int i = 0; i < scene->players.size(); ++i){
		scene->players[i]->updatePlayerOrientation();
	}
}

void GameEngine::initOGL(){
	srand((unsigned)time(0));

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

	sgct::ShaderManager::Instance()->bindShader( "SimpleColor" );
	currentTimeId = sgct::ShaderManager::Instance()->getShader( "SimpleColor").getUniformLocation( "currentTime" ); 
	globalRandomId = sgct::ShaderManager::Instance()->getShader( "SimpleColor").getUniformLocation( "globalRandom" ); 
	sgct::ShaderManager::Instance()->unBindShader();


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
	sgct::SharedData::Instance()->writeDouble(currentTime);
}

void GameEngine::decode(){
	currentTime = sgct::SharedData::Instance()->readDouble();
}

void GameEngine::keyCallback(int key, int action){
	//UGLY, but handy for testing without controller
	Player * p = scene->players[0];
	if(p){
		switch(key){
			case 'W': p->arrowButtons[p->FORWARD] = (action == GLFW_PRESS); break;
			case 'S': p->arrowButtons[p->BACKWARD] = (action == GLFW_PRESS);break;
			case 'A': p->arrowButtons[p->LEFT] = (action == GLFW_PRESS); break;
			case 'D': p->arrowButtons[p->RIGHT] = (action == GLFW_PRESS); break;
		}
	}
}

void GameEngine::mouseButtonCallback(int button, int action){

}
