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

int main(int argc, char* argv[]){


	gEngine = new sgct::Engine(argc, argv);
	gameEngine = new GameEngine();

	//Bind functions to our Game Engine
	gEngine->setDrawFunction(myDrawFun);
	gEngine->setInitOGLFunction(myInitOGLFun);

	if(!gEngine->init()){
		delete gEngine;
		return EXIT_FAILURE;
	}

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
