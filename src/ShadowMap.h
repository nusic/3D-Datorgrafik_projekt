#ifndef SHADOWMAP_H
#define SHADOWMAP_H

#include "sgct.h"
#include <iostream>


struct shadowMapData{

	GLuint depthMatrixID;
	GLuint depth_vertexPosition_modelspaceID;

	GLuint depthBiasID;
	GLuint shadowMapID;

};



#endif