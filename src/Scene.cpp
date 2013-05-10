#include "Scene.h"


Scene::Scene():
Model(new ModelMesh("data/meshes/bumpy.obj"), "SimpleTexture", "SimpleColor"){
	std::cout << "*** CREATED SCENE ***" << std::endl;

}

std::vector<LightSource*> Scene::lightSources;


Scene::~Scene(){

}

void Scene::initScene(){
	
	/*
	
	Innan ärvde klasserna från varandra såhär

					   Model
						 |	* ModelMatrix
						 |	* ModelMesh
						 |	* Texture
						 |	* Shader
						 |	
					GameObject
						 |	* position
						 |	* direction
						 |
			


	Nu har vi ny scengraph. Blir lite ny syntax nu.
	Så här ärver klasserna av varandra. 


						Node 
						 |  * vector<Node*> children
						 |  * Node* parent
						 | 	  virtual void draw(P, V, M);
						 |
		-------------------------------------
		|		 							|
	  Model   		 		 	  	  Transformation
	    |  * ModelMesh		 				| 	* glm::mat4 matrix
	    |  * Texture						|
	    |  * Shader				 			|
	  	|									|
	  Scene									---------------------
	  	   * vector<Player*>				|			|		|
		   * vector<LightSource*>		Translation   Scale   Rotation




	- GameObject ärver inte längre från Model
	- GameObject är i princip bara en kedja med Nodes:

			Translation->Rotation->Scale->Model

	*/
	
	Model* suzanne = new Model(new ModelMesh("data/meshes/suzanne.obj"), "SimpleTexture2", "SimpleColor");
	addChildNode(suzanne);

	Transformation* trans1 = new Translation(suzanne, 2.0f, 0.0f, 0.0f);
	Transformation* scale1 = new Scaling(trans1, 0.5f, 0.5f, 0.5f);
	Transformation* rot1 = new Rotation(scale1, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		Model* child1 = new Model(new ModelMesh("data/meshes/suzanne.obj"), "SimpleTexture2", "SimpleColor");
		rot1->addChildNode(child1);

	GameObject* go1 = new GameObject(-2,0,0);
	addChildNode(go1->getSceneGraphBranch());


	
	Player * body1 = new Player;
	body1->setPosition(0.0f, 0.0f, 5.0f);
	addPlayer(body1);

	/*
	Testa att sätt antal generationer till 
	ett större tal, som typ 10. Det slutar
	funka att ladda in texturer (för mig erik). 
	Är det grafikminnet som blir fullt tro?
	*/
	//addGenerations(body1->getMainModel(), 2);


	Player * body2 = new Player;
	body2->setPosition(-5.0f, 0.0f, 0.0f);
	addPlayer(body2);

	Player * body3 = new Player;
	body3->setPosition(5.0f, 0.0f, 0.0f);
	addPlayer(body3);

	Player * body4 = new Player;
	body4->setPosition(0.0f, 0.0f, -5.0f);
	addPlayer(body4);

	Player * body5 = new Player;
	body5->setPosition(0.0f, 0.0f, 0.0f);
	addPlayer(body5);

	Player * body6 = new Player;
	body6->setPosition(0.0f, 0.0f, -10.0f);
	addPlayer(body6);
	
}

void Scene::addPlayer(Player * p){
	addChildNode(p->getSceneGraphBranch());
	players.push_back(p);
	
}

void Scene::addGenerations(Model* mother, int n){
	if(n<=0)
		return;
	GameObject* child1 = new GameObject(2, 1, 1, 0.7);
	GameObject* child2 = new GameObject(-2, 1, 1, 0.7);
	
	mother->addChildNode(child1->getSceneGraphBranch());
	mother->addChildNode(child2->getSceneGraphBranch());

	addGenerations(child1->getMainModel(), n-1);
	addGenerations(child2->getMainModel(), n-1);

}


void Scene::drawScene(glm::mat4 P, glm::mat4 V) {
	draw(P, V, glm::mat4(1.0f));
}

void Scene::draw(glm::mat4 P, glm::mat4 V, glm::mat4 parentModelMatrix){
	Model::draw(P, V, parentModelMatrix);
}

