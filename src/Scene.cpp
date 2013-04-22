#include "Scene.h"


Scene::Scene(ModelMesh* _mesh = NULL, 
		  	 glm::mat4 M = glm::mat4(1.0), 
		  	 std::string _shaderName = "SimpleColor"){

}

Scene::~Scene(){

}

void Scene::initScene(){
	//children.push_back(*(new GameObject(0,0,0)));
}

void Scene::drawScene(glm::mat4 ViewPerspectiveMatrix) const {
	std::cout << "draw Scene" << std::endl;
	if
	drawModel(ViewPerspectiveMatrix);
}