#include "Scene.h"


Scene::Scene():
Model(new ModelMesh("data/meshes/testScene.obj"), glm::mat4(1.0f), "SimpleTexture", "SimpleColor"){
	std::cout << "*** CREATED SCENE ***" << std::endl;

}

Scene::~Scene(){

}

std::vector<LightSource*> Scene::lightSources;

void Scene::initScene(){
	
	GameObject suzanne(0, 2, 1, 1);
	//GameObject child1(2, 1, 1, 0.5);
	//GameObject child2(-2, 1, 1, 0.5);
	//suzanne.children.push_back(child1);
	//suzanne.children.push_back(child2);
	children.push_back(suzanne);

	GameObject c1(3, -3, 1);
	GameObject c2(-3, -3, 1);
	children.push_back(c1);
	children.push_back(c2);


	//OK, ljuset beter sig lite mystiskt. Av någon anledning ser det ut som om
	//det finns två ljuskällor trots att det bara är en (som cirkulerar)
	//och den ena apan blir ljusare (på grund av att han är närmare origo)
	//vilket är konstigt, borde inte vara så tycker jag.
	//Någon som har någon idé vad dessa saker kan bero på?
	//Som det är nu kan man bara ha en ljuskälla då vi bindar handles
	//manuellt för varje variabel ljuskällan har
	//(nu använder vi dock bara oss av positionen i shadersarna)
	//men vi läre ändå fixa så att det ser annorlunda ut senare
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

void Scene::drawScene(glm::mat4 P, glm::mat4 V) {
	drawModel(P, V, glm::mat4());
}
