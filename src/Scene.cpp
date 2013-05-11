#include "Scene.h"

Scene::Scene():
Model(new ModelMesh("data/meshes/plane.obj"), "SimpleTexture", "SimpleColor"){ 
	sceneDimensions = getMaxVertexValues() - getMinVertexValues();
}

std::vector<LightSource*> Scene::lightSources;

Scene::~Scene(){

}

void Scene::initScene(){

	/*

	Innan ärvde klasserna från varandra såhär

					   Model
					   	 |	* vector<Model*> children
						 |	* ModelMatrix
						 |	* ModelMesh
						 |	* Texture
						 |	* Shader
						 |	  void drawModel(P, V, localModelMatrix);
						 |
			-----------------------------
			|							|
		  Scene						GameObject
			  * vector<Player>			|	* position
			  * vector<LightSource> 	|	* direction
						 				|
						 		DynamicGameObject
						 				|	* velocity
						 				|	* angleVelocity
						 				|
						 			  Player
						 			  		* Controller
						 			  		* LightObject* head


==============================================================================


	Nu har vi ny scengraph. Blir lite ny syntax.
	Så här ärver klasserna av varandra nu.


							   Node
								|  * vector<Node*> children
							 	|  * Node* parent
							 	| 	  virtual void draw(P, V, M);
							 	|
		---------------------------------------------------------
		|		 				|								|
	  Model   		 		 LightSource			  	  	Transformation
	    |  * ModelMesh				* glm::vec3 position		| 	* glm::mat4 matrix
	    |  * Texture				* glm::vec3 direction		|
	    |  * Shader			 		* index						|
	  	|														|
	  Scene											---------------------
	  	   * vector<Player*>						|			|		|
		   * vector<LightSource*>				Translation   Scale   Rotation




	- GameObject ärver inte längre från Model
	- GameObject är i princip bara 4 Nodes som är ihop kopplade enligt

				Translation -> Rotation -> Scaling -> Model


		 GameObject
		 	 |	* glm::vec3 position
		 	 |	* glm::vec3 direction
		 	 |	* float phi, theta
			 |	* Translation
			 |	* Rotation
			 | 	* Scaling
			 | 	* Model
			 |	  Node* getSceneGraphBranch();
			 |
	 DynamicGameObject
	 		 |	* glm::vec3 velocity
			 |	* angleVelocity
			 |
		   Player
		  		* Controller
		  		* LightObject* head

	*/

	Model* suzanne = new Model(new ModelMesh("data/meshes/suzanne.obj"), "SimpleTexture2", "SimpleColor");
	addChildNode(suzanne);
/*
	Transformation* trans1 = new Translation(suzanne, 2.0f, 0.0f, 0.0f);
	Transformation* scale1 = new Scaling(trans1, 0.5f, 0.5f, 0.5f);
	Transformation* rot1 = new Rotation(scale1, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	Model* child1 = new Model(rot1, new ModelMesh("data/meshes/suzanne.obj"));


	GameObject* go1 = new GameObject(-2,0,0);
	addChildNode(go1->getSceneGraphBranch());


	*/
	Player * body1 = new Player;
	body1->setPosition(0.0f, 0.0f, 5.0f);
	addPlayer(body1);
	//Transformation* trans2 = new Translation(body1->getSceneGraphBranch(), 2.0f, 0.0f, 0.0f);
	//LightSource* l1 = new LightSource();
	//trans2->addChildNode(l1);

	/*
	Testa att sätt antal generationer till
	ett större tal, som typ 10. Det slutar
	funka att ladda in texturer (för erik).
	Är det grafikminnet som blir fullt tro?
	*/
	//addGenerations(body1->getMainModel(), 2);
/*
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

	Player * body7 = new Player;
	body7->setPosition(0.0f, 0.0f, 10.0f);
	addPlayer(body7);
*/

	followCamera = new FollowCamera(body1, 0.0f, 30.0f, 30.0f);

	std::string imgpath= "data/heightmap/heightmap.bmp";
    readBMP(imgpath.c_str());
}

void Scene::update(float dt){

	for (int i = 0; i < players.size(); ++i){
		players[i]->updatePlayerOrientation(
            dt,
            heightmap,
            heightmapWidth,
            heightmapHeight,
			sceneDimensions);
	}

	followCamera->updateLookAt();
	followCamera->incrementPosition(
		followCamera->target->getVelocity().x,
		followCamera->target->getVelocity().y,
		followCamera->target->getVelocity().z,
		dt);

	followCamera->calcMatrices();
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


float Scene::getZPosition(int x, int y){
    return *(heightmap + (x*y));
}

void Scene::readBMP(const char* filename)
{
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize;   // = width*height*3
    // Actual RGB data
    unsigned char * allData;

    // Open the file
    FILE * file = fopen(filename,"rb");
    if (!file){printf("Image could not be opened\n");}

    if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
    printf("Not a correct BMP file\n");
    }
    if ( header[0]!='B' || header[1]!='M' ){
    printf("Not a correct BMP file\n");
    }


    // Read ints from the byte array
    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);

    heightmapWidth = width;
    heightmapHeight = height;

    if (imageSize==0)    imageSize=width*height*3;
    if (dataPos==0)      dataPos=54;

    // Create a buffer
    allData = new unsigned char [imageSize];
    heightmap = new float[imageSize/3];

    fread(allData,1,imageSize,file);

    unsigned char maxDepth = allData[0];
    unsigned char minDepth = allData[0];
    for(int i = 0; i < imageSize; i+=3){
    	if(allData[i] > maxDepth) maxDepth = allData[i];
    	if(allData[i] < minDepth) minDepth = allData[i];
    }
    
    float scale = sceneDimensions.y / ( (float)(maxDepth - minDepth));
    
    for(int i = 0; i < imageSize; i+=3){
        heightmap[i/3] = (float)allData[i]*scale;
    }

    fclose(file);
}
