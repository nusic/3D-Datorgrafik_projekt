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

	//RENDER TO THE DEPTH BUFFERS
	//FRONT FACE CULLING IS ENABLED WHEN RENDERING TO DEPTH-BUFFER
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	int numOfLightSources = LightSource::getNumberOfLightSources();
	for (int i = 0; i < numOfLightSources; ++i){
		//Bind the framebuffer used for shadow mapping
		glBindFramebuffer(GL_FRAMEBUFFER, LightSource::FBO[i]);
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Render on the whole framebuffer
		glViewport(0,0,LightSource::SHADOW_MAP_RESOLUTION,LightSource::SHADOW_MAP_RESOLUTION); 
		scene->renderToDepthBuffer(glm::mat4(1.0f), i);
	}
	glDisable(GL_CULL_FACE);


	//RENDER TO THE SCREEN
	//Backface culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//Bind the default framebuffer (render to screen)
	glBindFramebuffer(GL_FRAMEBUFFER, 2);
	glViewport(0,0,640 * 2,360 * 2);
	scene->drawScene(camera->getPerspectiveMatrix(), camera->getViewMatrix());
/*
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

	glViewport(0,0,640,360);
	scene->drawScene(camera->getPerspectiveMatrix(), camera->getViewMatrix());

	glViewport(640,0,640,360);
	scene->drawScene(scene->followCamera->getPerspectiveMatrix(), scene->followCamera->getViewMatrix());
	glDisable(GL_CULL_FACE);
*/
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

	
	scene->update(dt);
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


	sgct::TextureManager::Instance()->loadTexure(
		"SimpleTexture", "data/textures/texture1.png", true);

	sgct::TextureManager::Instance()->loadTexure(
		"SimpleTexture2", "data/textures/texture2.png", true);

	//Creating the shader "SimpleColor"
	sgct::ShaderManager::Instance()->addShader(
		"SimpleColor", "data/shaders/simple.vert", "data/shaders/simple.frag");

	//Creating the shader "depthProgram"
	sgct::ShaderManager::Instance()->addShader(
		"depthProgram", "data/shaders/depthRRT.vert", "data/shaders/depthRRT.frag");

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

	camera->setPosition(0, 15, 15);
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
