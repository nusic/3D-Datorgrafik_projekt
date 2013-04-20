#include <vector> 
#include <string>
#include <stdio.h>
#include <cstring>

#include <glm/glm.hpp>

#include <sgct.h>

#ifndef MODEL_MESH_H
#define MODEL_MESH_H

class ModelMesh{
public:
	ModelMesh(const char* path);

	bool loadOBJ(const char* path);

	void generateGLBuffers();

	
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	GLuint vertexbuffer;
	GLuint normalbuffer;
	GLuint uvbuffer;
};

#endif