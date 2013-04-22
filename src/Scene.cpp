#include "Scene.h"


Scene::Scene():
Model(new ModelMesh("data/meshes/bullen.obj"), glm::mat4(1.0f), "SimpleColor"){
	std::cout << "*** CREATED SCENE ***" << std::endl;

}

Scene::~Scene(){

}

void Scene::initScene(){
	//children.push_back(*(new GameObject(0,0,0)));
}

void Scene::drawScene(glm::mat4 ViewPerspectiveMatrix) const {
	drawModel(ViewPerspectiveMatrix);
}