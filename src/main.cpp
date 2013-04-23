#include "sgct.h"
#include "Model.h"
#include "ModelMesh.h"
#include <iostream>
#include "GameEngine.h"
#include "Player.h"

sgct::Engine* gEngine;

GameEngine* gameEngine;

//Using globals here just to test
//The handle for the vertex-positions
GLuint vertexPosition_modelspaceID;

//Vertex data
static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	 1.0f, -1.0f, 0.0f,
	 0.0f,  1.0f, 0.0f,
};

//The ID for the vertexbuffer
GLuint vertexbuffer;

void myDrawFun();
void myInitOGLFun();

int main(int argc, char* argv[]){

	gEngine = new sgct::Engine(argc, argv);
	gameEngine = new GameEngine();

	//Bind the draw function, and the initOGL function
	gEngine->setDrawFunction(myDrawFun);
	gEngine->setInitOGLFunction(myInitOGLFun);


	if(!gEngine->init()){
		delete gEngine;
		return EXIT_FAILURE;
	}



	// Main loop
	gEngine->render();
    //delete gameEngine->player;
	// Clean up
	delete gEngine;

	// Exit program
	exit(EXIT_SUCCESS);
}

void myInitOGLFun(){

	gameEngine->initOGL();

/*
	//Creating the shader "SimpleColor"
	sgct::ShaderManager::Instance()->addShader("SimpleColor", "data/shaders/simple.vert", "data/shaders/simple.frag");
	sgct::ShaderManager::Instance()->bindShader("SimpleColor");

	//The handle for the position of a vertex
	vertexPosition_modelspaceID = sgct::ShaderManager::Instance()->getShader("SimpleColor").getAttribLocation("vertexPosition_modelspace");

	//Generate a buffer for the vertex list
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	sgct::ShaderManager::Instance()->unBindShader();
	*/
}

void myDrawFun(){

	gameEngine->draw();

	/*
	//Use the shader "SimpleColor"
	sgct::ShaderManager::Instance()->bindShader("SimpleColor");

	//Attribute the vertices buffer
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		vertexPosition_modelspaceID, // The attribute we want to configure
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangle!
	// 3 indices starting at 0 -> 1 triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);

	sgct::ShaderManager::Instance()->unBindShader();

	*/



}
