#include "GameEngine.h"

GameEngine::GameEngine(){
	renderWireFrame = false;
}

GameEngine::~GameEngine(){

}


void GameEngine::keyboardCallback(int key, int action){
	switch(key){
		case 'm':
		case 'M': if(action == SGCT_PRESS) toggleRenderMode(); break;
		case 'k':
		case 'K': scene->team1[0]->kill();
	}
}

void GameEngine::toggleRenderMode(){
	renderWireFrame = !renderWireFrame;
}

void GameEngine::draw(){
	sgct::ShaderManager::Instance()->bindShader( "SimpleColor" );
	glUniform1f(currentTimeId, static_cast<float>(currentTime));
	glUniform1f(globalRandomId, static_cast<float>(globalRandom));
	sgct::ShaderManager::Instance()->unBindShader();

	//RENDER TO THE DEPTH BUFFERS
	//FRONT FACE CULLING IS ENABLED WHEN RENDERING TO DEPTH-BUFFER


	int numOfLightSources = LightSource::getNumberOfLightSources();
	for (int i = 0; i < numOfLightSources; ++i){

		//Bind the framebuffer used for shadow mapping
		glBindFramebuffer(GL_FRAMEBUFFER_EXT, LightSource::FBO[i]);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Render on the whole framebuffer
		glViewport(0,0,LightSource::SHADOW_MAP_RESOLUTION,LightSource::SHADOW_MAP_RESOLUTION);
		glm::mat4 VP = LightSource::getVPFromIndex(i);
		glm::mat4 M(1.0f);

		scene->renderToDepthBuffer(VP, M);
		glDisable(GL_CULL_FACE);
	}




	//RENDER TO THE SCREEN

	glBindFramebuffer(GL_FRAMEBUFFER, DEFAULT_FBO_INDEX);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	if(renderWireFrame){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
	}
	for (int i = 0; i < scene->cameras.size(); ++i){
		glViewport(i * 640 * 2,0,640 * 2,360 * 2);
		scene->drawScene(
			scene->cameras[i]->getPerspectiveMatrix(),
			scene->cameras[i]->getViewMatrix());
	}

    glDisable(GL_CULL_FACE);

}

void GameEngine::preSync(float dt){
	currentTime = sgct::Engine::getTime();

	//gör så att vår stokastiska variabel "globalRandom" får en
	//kankse lite roligare fördelningsfunktions mha en sinus.
	//Ska likna brinnande eld var tanken dårå.
	globalRandom = sin(0.3f+rand()/(float)RAND_MAX);

	scene->update(dt);

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


	sgct::TextureManager::Instance()->loadTexure(
		"SimpleTexture", "data/textures/texture1.png", true);

	sgct::TextureManager::Instance()->loadTexure(
		"SimpleTexture2", "data/textures/texture2.png", true);

	sgct::TextureManager::Instance()->loadTexure(
		"Sublime", "data/textures/sublime.png", true);

	sgct::TextureManager::Instance()->loadTexure(
		"Ground", "data/textures/ground.png", true);


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


}

int GameEngine::getDefaultFBOindex() const{
	printf("\nTesting if some FBO indices are defined in OpenGL ... \n");
	int theIndex = -1;
	int N = LightSource::FBO[LightSource::FBO.size()-1]+10;
	for (int i = 0; i < N; ++i){
		printf("%2i : ", i);
		if(glIsFramebuffer(i)){
			printf("yes --> ");
			int forShadow = -1;
			for (int j = 0; j < LightSource::FBO.size(); ++j){
				if(i == LightSource::FBO[j]){
					forShadow = j;
					break;
				}
			}
			if(forShadow != -1)
				printf("shadowmap FBO[%i] = %i", forShadow, LightSource::FBO[forShadow]);
			else{
				printf("not declares as shadowmap. This can be the default screen FBO");
				theIndex = (theIndex == -1) ? i : -2;
			}
		}
		else
			printf("no  ");
		printf("\n");
	}
	printf("\n");
	if(theIndex == -1) printf("WARNING: Didn't find possible default index\n");
	if(theIndex == -2) printf("WARNING: Found 2 or more possible default index\n");
	return theIndex;
}

void GameEngine::encode(){
	sgct::SharedData::Instance()->writeDouble(currentTime);
}

void GameEngine::decode(){
	currentTime = sgct::SharedData::Instance()->readDouble();
}
