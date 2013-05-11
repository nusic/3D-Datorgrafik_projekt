#ifndef SCENE_H
#define SCENE_H

#include "sgct.h"
#include "Model.h"
#include "GameObject.h"
#include "LightSource.h"
#include "Player.h"
#include "Node.h"
#include "Transformation.h"
#include <vector>
#include "FollowCamera.h"


class Scene : public Model{
public:
	Scene();
	~Scene();

	void initScene();
	void drawScene(glm::mat4 P, glm::mat4 V);
	virtual void draw(glm::mat4 P, glm::mat4 V, glm::mat4 parentModelMatrix);
	void update(float dt);

	void addPlayer(Player * player);
	void addGenerations(Model* mother, int n);

    
	std::vector<Player*> players;
	FollowCamera* followCamera;
	static std::vector<LightSource*> lightSources;

	
	float getZPosition(int x, int y);
    float* heightmap;
    int heightmapWidth;
    int heightmapHeight;

    float sceneWidth;
    float sceneHeight;

private:

	void readBMP(const char* filename);

};

#endif
