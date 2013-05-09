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


	glViewport(0,0,640,360);
	scene->drawScene(camera->getPerspectiveMatrix(), camera->getViewMatrix());

	glViewport(640,0,640,360);
	scene->drawScene(camera2->getPerspectiveMatrix(), camera2->getViewMatrix());
}

void GameEngine::preSync(float dt){
	currentTime = sgct::Engine::getTime();

	//gör så att vår stokastiska variabel "globalRandom" får en
	//kankse lite roligare fördelningsfunktions mha en sinus.
	//Ska likna brinnande eld var tanken dårå.
	globalRandom = sin(0.3f+rand()/(float)RAND_MAX);

	camera->incrementPosition(dt);
	camera->calcMatrices();

	camera2->incrementPosition(dt);
	camera2->calcMatrices();

	for (int i = 0; i < scene->players.size(); ++i){
		scene->players[i]->updatePlayerOrientation(dt);
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
//	glEnable(GL_CULL_FACE);


	sgct::TextureManager::Instance()->loadTexure(
		"SimpleTexture", "data/textures/texture1.png", true);

	sgct::TextureManager::Instance()->loadTexure(
		"SimpleTexture2", "data/textures/texture2.png", true);

	//Creating the shader "SimpleColor"
	sgct::ShaderManager::Instance()->addShader(
		"SimpleColor", "data/shaders/simple.vert", "data/shaders/simple.frag");

	assert(sgct::ShaderManager::Instance()->bindShader( "SimpleColor" ));
	currentTimeId = sgct::ShaderManager::Instance()->getShader( "SimpleColor").getUniformLocation( "currentTime" );
	globalRandomId = sgct::ShaderManager::Instance()->getShader( "SimpleColor").getUniformLocation( "globalRandom" );
	sgct::ShaderManager::Instance()->unBindShader();


	scene = new Scene();
	scene->initScene();

	camera = new Camera(-30, -5, 15);
	camera->setLookAt(0, 0, 0);
	camera->setVelocity(0.05, 0.02, -0.01);

	//Uncomment the two lines below to get simple static front view
	camera->setPosition(0, 30, 30);
	camera->setVelocity(0, 0, 0);


	camera2 = new Camera(0, 30, -30);
	camera2->setLookAt(0, 0, 0);
}

void GameEngine::encode(){
	sgct::SharedData::Instance()->writeDouble(currentTime);
}

void GameEngine::decode(){
	currentTime = sgct::SharedData::Instance()->readDouble();
}
