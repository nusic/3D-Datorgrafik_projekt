
//#define NDEBUG

#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <iostream>
#include <string>
#include <cassert>

#include "ModelMesh.h"
#include "Node.h"
#include "LightSource.h"
#include "sgct.h"
#include "Camera.h"



class Model : public Node{
public:
	Model(const std::string &meshName = "tree2",
		  std::string _textureName = "SimpleTexture",
		  std::string _shaderName = "SimpleColor");
	Model(Node* _parent = NULL, const std::string &meshName = "tree2",
		  std::string _textureName = "SimpleTexture",
		  std::string _shaderName = "SimpleColor");
	
	virtual ~Model();

	void setShader(std::string _shaderName);
	void setMesh(ModelMesh * _mesh);
	void setTexture(std::string _textureName);

	ModelMesh* getMesh() const;

	

    bool hasMesh() const;

	friend class Scene;

    virtual int getNumberOfVertices() const;
    virtual void renderToScreen(const glm::mat4 &P, const glm::mat4 &V, const glm::mat4 &M);
    virtual void renderToDepthBuffer(const glm::mat4 &VP, const glm::mat4 &M);

private:

	ModelMesh* mesh;
	std::string shaderName;

	//Handles for the shader
	GLuint vertexPositionID;
	GLuint vertexUVID;
	GLuint vertexNormalID;


	GLuint textureID;

	GLuint modelMatrixID;
	GLuint viewMatrixID;
	GLuint modelViewMatrixID;
	GLuint modelViewPerspectiveMatrixID;

	//Handle for matrix and texture
	GLuint texture;

};


#endif
