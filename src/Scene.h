#ifndef SCENE_H
#define SCENE_H

#include "sgct.h"
#include "Model.h"
#include "GameObject.h"
#include "LightSource.h"
#include "Player.h"
#include <vector>
#include "FollowCamera.h"


class Scene : public Model{
public:
	Scene();

	~Scene();

	void initScene();
	void drawScene(glm::mat4 P, glm::mat4 V);

	void addPlayer(Player * player);

	void addGenerations(Model* mother, int n);

    float getZPosition(int x, int y);

    void readBMP(const char* filename);

	static std::vector<LightSource*> lightSources;

	std::vector<Player*> players;
	FollowCamera* followCamera;

private:
    float* heightmap;
};

#endif
