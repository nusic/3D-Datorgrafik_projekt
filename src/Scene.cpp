#include "Scene.h"

Scene::Scene():
Model(new ModelMesh("data/meshes/plane.obj"), glm::mat4(1.0f), "SimpleTexture", "SimpleColor"){
	std::cout << "*** CREATED SCENE ***" << std::endl;

}

std::vector<LightSource*> Scene::lightSources;

Scene::~Scene(){

}

void Scene::initScene(){

	GameObject* suzanne = new GameObject(0, 1.5, 1, 1);
	GameObject* child1 = new GameObject(2, 0, 1, 0.5);
	GameObject* child2 = new GameObject(-2, 0, 1, 0.5);
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

	Player * body1 = new Player;
	body1->setPosition(0.0f, 0.0f, 5.0f);
	addPlayer(body1);

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

    readBMP("data/heightmap/heightmap.bmp");
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

float Scene::getZPosition(int x, int y){
    return *(heightmap + (x*y));
}

void Scene::readBMP(char* filename)
{
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize;   // = width*height*3
    // Actual RGB data
    unsigned char * data;
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

    if (imageSize==0)    imageSize=width*height*3;
    if (dataPos==0)      dataPos=54;

    // Create a buffer
    allData = new unsigned char [imageSize];
    data = new unsigned char [imageSize/3];

    fread(allData,1,imageSize,file);

    for(int i = 0; i < imageSize; i+=3)
        data[i/3] = allData[i];

    fclose(file);
}
