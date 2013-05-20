#include "StaticGameObject.h"

StaticGameObject::StaticGameObject(float x, float y, float z, float scale, float phi, float theta){
	transformationNode = new Transformation();
	setPosition(x,y,z);
	setSize(scale, scale, scale);
	setRotation(phi, theta);

	modelNode = new Model(transformationNode, "data/meshes/suzanne.obj", "SimpleTexture2", "SimpleColor");
}

StaticGameObject::StaticGameObject(std::string objfile, std::string texture, std::string shader){
	transformationNode = new Transformation();
	setPosition(0.0f, 0.0f, 0.0f);
	setSize(1.0f, 1.0f, 1.0f);
	setRotation(0.0f, 0.0f);

	modelNode = new Model(transformationNode, objfile, texture, shader);
}

StaticGameObject::~StaticGameObject(){
	//delete transformationNode;
}

void StaticGameObject::setYPosition(float y){
	transformationNode->matrix[3][1] = y;
}

void StaticGameObject::setPosition(float x, float y, float z){
	transformationNode->matrix[3][0] = x;
	transformationNode->matrix[3][1] = y;
	transformationNode->matrix[3][2] = z;
}

void StaticGameObject::setSize(float x, float y, float z){
	transformationNode->matrix[0][0] = x;
	transformationNode->matrix[1][1] = y;
	transformationNode->matrix[2][2] = z;
}

void StaticGameObject::setSize(float s){
	transformationNode->matrix[0][0] = s;
	transformationNode->matrix[1][1] = s;
	transformationNode->matrix[2][2] = s;
}

void StaticGameObject::setRotation(float phi, float theta){
	transformationNode->matrix = glm::rotate(transformationNode->matrix, phi, glm::vec3(0.0f, 1.0f, 0.0f));
	transformationNode->matrix = glm::rotate(transformationNode->matrix, theta, glm::vec3(1.0f, 0.0f, 0.0f));
}

Node* StaticGameObject::getSceneGraphBranch() const{
	return transformationNode;
}

