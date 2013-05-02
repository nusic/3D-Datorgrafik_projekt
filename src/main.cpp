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

void keyCallback(int key, int action);
void mouseButtonCallback(int button, int action);

int main(int argc, char* argv[]){


	gEngine = new sgct::Engine(argc, argv);
	gameEngine = new GameEngine();

	//Bind functions to our Game Engine
	gEngine->setDrawFunction(myDrawFun);
	gEngine->setInitOGLFunction(myInitOGLFun);
	gEngine->setPreSyncFunction(myPreSyncFun);

	gEngine->setKeyboardCallbackFunction(keyCallback);
	gEngine->setMouseButtonCallbackFunction(mouseButtonCallback);


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
	delete gEngine;

	// Exit program
	exit(EXIT_SUCCESS);
}

void myInitOGLFun(){
	gameEngine->initOGL();
}

void myPreSyncFun(){
	gameEngine->preSync();
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

void keyCallback(int key, int action){

}

void mouseButtonCallback(int button, int action){

}