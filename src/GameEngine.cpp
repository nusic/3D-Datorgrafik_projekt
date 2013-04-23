#include "GameEngine.h"

GameEngine::GameEngine(){

}

GameEngine::~GameEngine(){

}

float angle2 = 0.0f;
float da = 0.8f;
void GameEngine::draw(){
    //player->updatePlayerOrientation();
	angle2 += da;
	da *= 0.997f;

	float d = 10.0f;
	glm::vec3 position(d, 1.5f*d, d);
	glm::vec3 direction(-1.0f, -1.0f, -1.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	glm::mat4 View = glm::lookAt(
		position,           // Camera is here
		position+direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );

	glm::mat4 View2 = glm::rotate(View, angle2, up);

	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);


	scene->drawScene(Projection * View2);
	//player->drawModel(Projection * View2);
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

	sgct::TextureManager::Instance()->loadTexure("SimpleTexture", "data/textures/texture1.png", true);

	//Creating the shader "SimpleColor"
	sgct::ShaderManager::Instance()->addShader("SimpleColor", "data/shaders/simple.vert", "data/shaders/simple.frag");
	if(!sgct::ShaderManager::Instance()->bindShader("SimpleColor"))
		std::cout << "ERROR: unable to bind shader!" << std::endl;

	scene = new Scene();
	scene->initScene();
	sgct::ShaderManager::Instance()->unBindShader();
    //player = new Player;


}

void GameEngine::encode(){

}

void GameEngine::decode(){

}
