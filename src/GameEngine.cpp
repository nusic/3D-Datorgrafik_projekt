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
		case 'K': if(action == SGCT_PRESS) scene->team[0]->players[0]->kill(); break;
		case 'r':
		case 'R': if(action == SGCT_PRESS){
			for (int i = 0; i < scene->team.size(); ++i){
				for (int j = 0; j < scene->team[i]->players.size(); ++j){
					scene->team[i]->players[j]->revive();
				}
			}
			break;
		}
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

		// Use our shader
		assert(sgct::ShaderManager::Instance()->bindShader("depthProgram"));
		scene->renderToDepthBuffer(VP, M);
		//Don't use the currently bound shader anymore
		sgct::ShaderManager::Instance()->unBindShader();

		glDisable(GL_CULL_FACE);

/*
		if(i == -1){
			//Bind the framebuffer used for shadow mapping
			glBindFramebuffer(GL_FRAMEBUFFER_EXT, LightSource::FBO[i]);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
			
			// Clear the screen
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Render on the whole framebuffer
			glViewport(0,0,LightSource::SHADOW_MAP_RESOLUTION,LightSource::SHADOW_MAP_RESOLUTION);
			glm::mat4 VP = LightSource::getVPFromIndex(i);
			//glm::mat4 M(1.0f);
			// Use our shader
			assert(sgct::ShaderManager::Instance()->bindShader("depthProgram"));
			scene->renderToDepthBuffer(VP, M);


			glDisable(GL_CULL_FACE);
		}
		*/
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

	float scale = 2.30f;
	const int xSize = scale * 640;
	const int ySize = scale * 360;
	for (int i = 0; i < scene->team.size(); ++i){
		glViewport(i * xSize, 0, xSize, ySize);
		scene->drawScene(
			scene->team[i]->camera->getPerspectiveMatrix(),
			scene->team[i]->camera->getViewMatrix());
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
	printf("\ninit GameEngine\n");
	
	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Enable blending -> render with alpha channel
	glEnable(GL_BLEND);

	// How to blend (?)
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//Loading textures
	sgct::TextureManager::Instance()->loadTexure("SimpleTexture", 			"data/textures/texture1.png", true);
	sgct::TextureManager::Instance()->loadTexure("SimpleTexture2", 			"data/textures/texture2.png", true);
	sgct::TextureManager::Instance()->loadTexure("tp4_texture", "data/textures/tp4_texture.png", true);
	sgct::TextureManager::Instance()->loadTexure("ghost_head_texture", 		"data/textures/ghost_head_texture.png", true);
	sgct::TextureManager::Instance()->loadTexure("ghost_body_texture", 		"data/textures/ghost_body_texture.png", true);
	sgct::TextureManager::Instance()->loadTexure("ghost_arm_right_texture",	"data/textures/ghost_arm_right_texture.png", true);
	sgct::TextureManager::Instance()->loadTexure("pick_axe_texture", 		"data/textures/pick_axe_texture.png", true);
	sgct::TextureManager::Instance()->loadTexure("flash_light_texture", 	"data/textures/flash_light_texture.png", true);
	sgct::TextureManager::Instance()->loadTexure("moon_texture", 			"data/textures/moon_texture.png", true);
	sgct::TextureManager::Instance()->loadTexure("ground_texture", 					"data/textures/ground.png", true);
	sgct::TextureManager::Instance()->loadTexure("table_texture", 			"data/textures/table_texture2.png", true);


	//Add shaders
	sgct::ShaderManager::Instance()->addShader("SimpleColor", "data/shaders/simple.vert", "data/shaders/simple.frag");
	sgct::ShaderManager::Instance()->addShader("depthProgram", "data/shaders/depthRRT.vert", "data/shaders/depthRRT.frag");
	sgct::ShaderManager::Instance()->addShader("heightProgram", "data/shaders/depthRRT.vert", "data/shaders/height.frag");


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
