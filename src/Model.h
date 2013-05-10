
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



class Model : public Node{
public:
	Model(ModelMesh* _mesh = NULL, 
		  std::string _textureName = "SimpleTexture",
		  std::string _shaderName = "SimpleColor");
	Model(Node* _parent = NULL, ModelMesh* _mesh = NULL,
		  std::string _textureName = "SimpleTexture",
		  std::string _shaderName = "SimpleColor");

	virtual ~Model();

	void setShader(std::string _shaderName);
	void setMesh(ModelMesh * _mesh);
	void setTexture(std::string _textureName);

    bool hasMesh() const;

	friend class Scene;
    void drawModel(glm::mat4 P, glm::mat4 V, glm::mat4 M);


    virtual void draw(glm::mat4 &P, glm::mat4 &V, glm::mat4 &M);


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
