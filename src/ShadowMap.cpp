#include "ShadowMap.h"

//using namespace shadowMap;


GLuint ShadowMap::framebufferName;
GLuint ShadowMap::depthTexture;

GLuint ShadowMap::depthMatrixID;
GLuint ShadowMap::depth_vertexPosition_modelspaceID;

GLuint ShadowMap::depthBiasID;
GLuint ShadowMap::shadowMapID;

glm::mat4 ShadowMap::biasMatrix(
		0.5, 0.0, 0.0, 0.0, 
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);

bool ShadowMap::initShadowMapBuffers(){

	//Creating the shader "depthProgram"
	sgct::ShaderManager::Instance()->addShader(
		"depthProgram", "data/shaders/depthRRT.vert", "data/shaders/depthRRT.frag");

	
	// Get a handle for our "MVP" uniform
	depthMatrixID = sgct::ShaderManager::Instance()->getShader( "depthProgram").getUniformLocation( "depthMVP" );
	// Get a handle for our buffers
	depth_vertexPosition_modelspaceID = sgct::ShaderManager::Instance()->getShader( "depthProgram").getAttribLocation( "vertexPosition_modelspace" );
	
	// ---------------------------------------------
	// Render to Texture - specific code begins here
	// ---------------------------------------------

	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	framebufferName = 0;
	glGenFramebuffers(1, &framebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferName);

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 256, 256, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
		 
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

	// No color output in the bound framebuffer, only depth.
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	// Always check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		std::cout << "FRAMEBUFFER IS NOT OK!!!" << std::endl;
		return false;
	}

	return true;

	/*
	// Create and compile our GLSL program from the shaders
	sgct::ShaderManager::Instance()->addShader(
		"quadProgram", "data/shaders/passThrough.vert", "data/shaders/simpleTexture.frag");
	GLuint texID = sgct::ShaderManager::Instance()->getShader( "quadProgram").getUniformLocation( "renderedTexture" );
	GLuint timeID = sgct::ShaderManager::Instance()->getShader( "quadProgram").getUniformLocation( "time" );

	// Get a handle for our buffers
	GLuint quad_vertexPosition_modelspaceID = sgct::ShaderManager::Instance()->getShader( "quadProgram").getAttribLocation( "vertexPosition_modelspace" );
	*/




	// Create and compile our GLSL program from the shaders
	//GLuint programID = LoadShaders( "ShadowMapping_SimpleVersion.vertexshader", "ShadowMapping_SimpleVersion.fragmentshader" );

	// Get a handle for our "MVP" uniform
	//GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	//GLuint DepthBiasID = glGetUniformLocation(programID, "DepthBiasMVP");
	//GLuint ShadowMapID = glGetUniformLocation(programID, "shadowMap");
	
	/*
	GLuint DepthBiasID = sgct::ShaderManager::Instance()->getShader( "SimpleColor").getUniformLocation( "DepthBiasMVP" );
	GLuint ShadowMapID = sgct::ShaderManager::Instance()->getShader( "SimpleColor").getUniformLocation( "shadowMap" );
	*/

	// Get a handle for our buffers
	//GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	//GLuint vertexUVID = glGetAttribLocation(programID, "vertexUV");

	// Get a handle for our "LightPosition" uniform
	//GLuint lightInvDirID = glGetUniformLocation(programID, "LightInvDirection_worldspace");
}
/*
void ShadowMap::renderToFrameBuffer(){
	// Render to our framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferName);
	glViewport(0,0,1024,1024); // Render on the whole framebuffer, complete from the lower left corner to the upper right

	// We don't use bias in the shader, but instead we draw back faces, 
	// which are already separated from the front faces by a small distance 
	// (if your geometry is made this way)
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); // Cull back-facing triangles -> draw only front-facing triangles

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use our shader
	sgct::ShaderManager::Instance()->bindShader(depthProgram);


	glm::vec3 lightDir = glm::vec3(LightSource::getDirectionArray()[0]);

	// Compute the MVP matrix from the light's point of view
	//glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10,10,-10,10,-10,20);
	//glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0,0,0), glm::vec3(0,1,0));
	// or, for spot light :
	glm::vec3 lightPos(LightSource::getPositionArray()[0]);
	glm::mat4 depthProjectionMatrix = glm::perspective<float>(45.0f, 1.0f, 2.0f, 50.0f);
	glm::mat4 depthViewMatrix = glm::lookAt(lightPos, lightPos + lightDir, glm::vec3(0,1,0));

	glm::mat4 depthModelMatrix = glm::mat4(1.0);
	glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(depthMatrixID, 1, GL_FALSE, &depthMVP[0][0]);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		depth_vertexPosition_modelspaceID,  // The attribute we want to configure
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		indices.size(),    // count
		GL_UNSIGNED_SHORT, // type
		(void*)0           // element array buffer offset
	);

	glDisableVertexAttribArray(0);
}
*/
