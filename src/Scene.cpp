#include "Scene.h"


Scene::Scene():
Model(new ModelMesh("data/meshes/bumpy.obj"), glm::mat4(1.0f), "SimpleTexture", "SimpleColor"){
	std::cout << "*** CREATED SCENE ***" << std::endl;

}

std::vector<LightSource*> Scene::lightSources;


Scene::~Scene(){

}

void Scene::initScene(){

	GameObject* suzanne = new GameObject(0, 2, 1, 1);
	GameObject* child1 = new GameObject(2, 1, 1, 0.5);
	GameObject* child2 = new GameObject(-2, 1, 1, 0.5);
	suzanne->children.push_back(child1);
	suzanne->children.push_back(child2);
	children.push_back(suzanne);

	GameObject* c1 = new GameObject(3, -3, 1);
	GameObject* c2 = new GameObject(-3, -3, 1);
	children.push_back(c1);
	children.push_back(c2);


//	LightSource* light1 = new LightSource(-3,2,-3);
//	LightSource* light2 = new LightSource(10,1,5);
//
//	light1->setColor(0.7,0.9,0.8);
//	light1->setDirectional(false);
//	light1->setIntensity(5);
//
//	light2->setColor(0.9,0.6,0.6);
//	light2->setDirectional(false);
//	light2->setIntensity(5);


//	Scene::lightSources.push_back(light1);
//	Scene::lightSources.push_back(light2);


	/*
	GameObject* anne = new GameObject(0, 4, 0);
	anne->setDirection(0.0f, 0.0f);
	anne->updateMatrix();

	addGenerations(anne, 5);
	children.push_back(anne);
	*/


	Player * body = new Player;
	body->setPosition(0.0f, 0.0f);
	//GameObject* head = new GameObject(0,2,0);
	//body->children.push_back(head);

	addPlayer(body);

	Player * body2 = new Player;
	body2->setPosition(0.0f, 0.0f);
	GameObject* head2 = new GameObject(0,2,0);
	body2->children.push_back(head2);
	addPlayer(body2);

	Player * body3 = new Player;
	body3->setPosition(0.0f, 0.0f);
	GameObject* head3 = new GameObject(0,2,0);
	body3->children.push_back(head3);
	addPlayer(body3);

}

void Scene::addPlayer(Player * p){
	children.push_back(p);
	players.push_back(p);

}

void Scene::addGenerations(Model* mother, int n){
	if(n<0)
		return;
	GameObject* child1 = new GameObject(2, 1, 1, 0.5);
	GameObject* child2 = new GameObject(-2, 1, 1, 0.5);
	mother->children.push_back(child1);
	mother->children.push_back(child2);

	addGenerations(mother->children[0], n-1);
	addGenerations(mother->children[1], n-1);
}


void Scene::drawScene(glm::mat4 P, glm::mat4 V) {
	drawModel(P, V, glm::mat4());
}
