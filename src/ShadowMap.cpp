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
	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 128, 128, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	glTexParameteri( shadowMapID , GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB );
		 
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
