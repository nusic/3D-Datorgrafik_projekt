#include "sgct.h"

sgct::Engine* gEngine;


void myDrawFun();

 
int main( int argc, char* argv[] )
{
	gEngine = new sgct::Engine( argc, argv );

	if( !gEngine->init() )
	{
		delete gEngine;
		return EXIT_FAILURE;
	}
 
 	//Bind your draw function to the render loop
	gEngine->setDrawFunction( myDrawFun );

	// Main loop
	gEngine->render();
 
	// Clean up
	delete gEngine;
 
	// Exit program
	exit( EXIT_SUCCESS );
}

void myDrawFun()
{
};