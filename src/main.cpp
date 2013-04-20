#include "sgct.h"
#include "Model.h"

sgct::Engine* gEngine;


void myDrawFun();

 
int main( int argc, char* argv[] )
{
	//Model m;
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
	//render a single triangle
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f); //Red
		glVertex3f(-0.5f, -0.5f, 0.0f);
 
		glColor3f(0.0f, 1.0f, 0.0f); //Green
		glVertex3f(0.0f, 0.5f, 0.0f);
 
		glColor3f(0.0f, 0.0f, 1.0f); //Blue
		glVertex3f(0.5f, -0.5f, 0.0f);
	glEnd();
}