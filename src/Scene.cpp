#include "Scene.h"


Scene::Scene():
Model(new ModelMesh("data/meshes/testScene.obj"), glm::mat4(1.0f), "SimpleColor"){
	std::cout << "*** CREATED SCENE ***" << std::endl;

}

Scene::~Scene(){

}

void Scene::initScene(){
	GameObject suzanne(0, 3, 1);
	GameObject child1(2, 1, 0.5);
	GameObject child2(-2, 1, 0.5);
	suzanne.children.push_back(child1);
	suzanne.children.push_back(child2);
	children.push_back(suzanne);
}

void Scene::drawScene(glm::mat4 ViewPerspectiveMatrix) {
	drawModel(ViewPerspectiveMatrix);
}
