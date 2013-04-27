#include "Scene.h"


Scene::Scene():
Model(new ModelMesh("data/meshes/testScene.obj"), glm::mat4(1.0f), "SimpleTexture", "SimpleColor"){
	std::cout << "*** CREATED SCENE ***" << std::endl;

}

Scene::~Scene(){

}

std::vector<LightSource*> Scene::lightSources;

void Scene::initScene(){
	GameObject suzanne(0, 3, 1, 1);
	GameObject child1(2, 1, 1, 0.5);
	GameObject child2(-2, 1, 1, 0.5);
	suzanne.children.push_back(child1);
	suzanne.children.push_back(child2);
	children.push_back(suzanne);

	GameObject c1(3, -3, 1);
	GameObject c2(-3, -3, 1);
	children.push_back(c1);
	children.push_back(c2);

	LightSource* light1 = new LightSource(0,0,0,"SimpleColor");

	Scene::lightSources.push_back(light1);

//	GameObject anne(0, 2, 4.0f);
//	anne.setDirection(180.0f, 0.0f);
//	anne.updateMatrix();

//	addGenerations(anne, 5);
//	children.push_back(anne);
}

void Scene::addGenerations(Model& mother, int n){
	if(n<0)
		return;
	GameObject child1(2, 1, 1, 0.5);
	GameObject child2(-2, 1, 1, 0.5);
	mother.children.push_back(child1);
	mother.children.push_back(child2);

	addGenerations(mother.children[0], n-1);
	addGenerations(mother.children[1], n-1);
}

void Scene::drawScene(glm::mat4 ViewPerspectiveMatrix) {
	drawModel(ViewPerspectiveMatrix);
}
