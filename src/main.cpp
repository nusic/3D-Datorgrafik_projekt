#include <iostream>

#include "sgct.h"
#include "GameEngine.h"

sgct::Engine* gEngine;

GameEngine* gameEngine;

void myInitOGLFun();
void myPreSyncFun();
void myDrawFun();

void myEncodeFun();
void myDecodeFun();

void myKeyboardCallbackFun(int key, int action);

int main(int argc, char* argv[]){

	gEngine = new sgct::Engine(argc, argv);
	gameEngine = new GameEngine();

	//Bind functions to our Game Engine
	gEngine->setDrawFunction(myDrawFun);
	gEngine->setInitOGLFunction(myInitOGLFun);
	gEngine->setPreSyncFunction(myPreSyncFun);
	gEngine->setKeyboardCallbackFunction(myKeyboardCallbackFun);


	if(!gEngine->init()){
		delete gEngine;
		return EXIT_FAILURE;
	}


	sgct::SharedData::Instance()->setEncodeFunction(myEncodeFun);
	sgct::SharedData::Instance()->setDecodeFunction(myDecodeFun);

	// Main loop
	gEngine->render();
    delete gameEngine;


	// Clean up
	sgct::ShaderManager::Destroy();
	delete gEngine;

	// Exit program
	exit(EXIT_SUCCESS);
}

void myInitOGLFun(){
	printf("\ninit GameEngine ... \n");
	gameEngine->initOGL();
}

void myPreSyncFun(){
	//sgct::MessageHandler::Instance()->print(
	//	"synctime = %.5f  drawtime = %0.5f  frametime = %0.5f",
	//	gEngine->getSyncTime(), gEngine->getDrawTime(), gEngine->getDt() );
	//sgct::MessageHandler::Instance()->print("\r");

	if(gEngine->isMaster())
		gameEngine->preSync(gEngine->getDt());
}

void myDrawFun(){
	gameEngine->draw();
}

void myEncodeFun(){
	gameEngine->encode();
}

void myDecodeFun(){
	gameEngine->decode();
}

void myKeyboardCallbackFun(int key, int action){
	gameEngine->keyboardCallback(key, action);
}
