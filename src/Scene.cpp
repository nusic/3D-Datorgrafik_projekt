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

	followCamera = new FollowCamera(body1, 0.0f, 30.0f, 30.0f);

	std::string imgpath= "data/heightmap/heightmap_test.bmp";
    //readBMP(imgpath.c_str());
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

void Scene::readBMP(const char* filename)
{
    FILE* f = fopen(filename, "rb");
    if(f){
	    unsigned char info[54];
	    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

	    // extract image height and width from header
	    int width = *(int*)&info[18];
	    int height = *(int*)&info[22];

	    int size = 3 * width * height;
	    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
	    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
	    fclose(f);

	//    for(int i = 0; i < size; i += 3)
	//    {
	//            unsigned char tmp = data[i];
	//            data[i] = data[i+2];
	//            data[i+2] = tmp;
	//    }

	    heightmap = new float[width*height]; //new heightmap

	    float scale = 0.1f;
	    for(int i = 0; i < width*height; i++)
	    {
	        heightmap[i] = scale*(float)data[i*3];
	    }

	//    for(int i = 0; i < width; i++)
	//    {
	//        for(int j = 0; j < height; j++)
	//        {
	//            heightmap[i*j] = scale*(float)data[k];
	//            k += 3;
	//        }
	//    }
}
}
