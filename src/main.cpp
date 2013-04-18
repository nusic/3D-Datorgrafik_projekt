#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "sgct.h"
#include "MyEngine.h"

#ifdef _TEST_
	int runUnitTests(int argc, char **argv);
#endif

sgct::Engine * gEngine;
MyEngine *mEngine;

void myDrawFun();
void myPreSyncFun();
void myInitOGLFun();
void myEncodeFun();
void myDecodeFun();


int main( int argc, char* argv[] )
{
#ifdef _TEST_
	if(runUnitTests(argc, argv ))
	{
		std::cin.get();
	}
#endif


	gEngine = new sgct::Engine( argc, argv );
	mEngine = new MyEngine();

	gEngine->setInitOGLFunction( myInitOGLFun );
	gEngine->setDrawFunction( myDrawFun );
	gEngine->setPreSyncFunction( myPreSyncFun );

	if( !gEngine->init() )
	{
		delete gEngine;
		return EXIT_FAILURE;
	}

	sgct::SharedData::Instance()->setEncodeFunction(myEncodeFun);
	sgct::SharedData::Instance()->setDecodeFunction(myDecodeFun);

	// Main loop
	gEngine->render();

	// Clean up
	sgct::ShaderManager::Destroy();
	delete gEngine;
	delete mEngine;

	// Exit program
	exit( EXIT_SUCCESS );
}

void myDrawFun()
{
	mEngine->myDrawFun();
}

void myInitOGLFun()
{
	mEngine->setMaster(gEngine->isMaster());
	mEngine->myInitOGLFun();
}

void myEncodeFun()
{
	mEngine->myEncodeFun();
}

void myDecodeFun()
{
	mEngine->myDecodeFun();
}

void myPreSyncFun()
{
	mEngine->myPreSyncFun();
}