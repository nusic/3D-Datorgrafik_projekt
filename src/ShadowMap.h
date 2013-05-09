#ifndef SHADOWMAP_H
#define SHADOWMAP_H

#include "sgct.h"
#include <iostream>



class ShadowMap{
public:
	static GLuint framebufferName;
	static GLuint depthTexture;

	static GLuint depthMatrixID;
	static GLuint depth_vertexPosition_modelspaceID;

	static GLuint depthBiasID;
	static GLuint shadowMapID;

	static glm::mat4 biasMatrix;

	static bool initShadowMapBuffers();
	static void renderToFrameBuffer();

};




#endif