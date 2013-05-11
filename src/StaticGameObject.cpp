#include "StaticGameObject.h"

StaticGameObject::StaticGameObject(float x, float y, float z, float scale, float _phi, float _theta){
	transformationNode = new Transformation();


	modelNode = new Model(transformationNode, new ModelMesh("data/meshes/suzanne.obj"), "SimpleTexture2", "SimpleColor");
}

StaticGameObject::~StaticGameObject(){
	delete transformationNode;
}

