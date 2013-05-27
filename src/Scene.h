#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <new>
#include <iostream>
#include <iomanip>


#include "sgct.h"
#include "Model.h"
#include "GameObject.h"
#include "StaticGameObject.h"
#include "LightSource.h"
#include "Player.h"
#include "Node.h"
#include "Transformation.h"
#include "FollowCamera.h"
#include "Team.h"

class Scene : public Model{
public:
	Scene();
	~Scene();

	void initScene();
	void initStaticPhysicalObjects();
	void initStaticNonPhysicalObjects();
	void initDynamicObjects();

	void drawScene(glm::mat4 P, glm::mat4 V);
	
	virtual void renderToScreen(glm::mat4 P, glm::mat4 V, glm::mat4 parentModelMatrix);
	bool renderToHeightMap(int xRes, int yRes);

	void update(float dt);
	void playerAttack(Player * p, int teamIndex);
	void playerRevive(Player * p, int teamIndex);

	void addPlayer(Player * player);
	void addPlayerToTeam(int index, Player * player);
	
	void addGenerations(Model* mother, int n);

    
	std::vector<Team*> team;

	static std::vector<LightSource*> lightSources;
	
	float getYPosition(float x, float z);
    float* heightmap;
    int heightmapWidth;
    int heightmapHeight;
    int heightmapArrayLength;

    float worldToHeightmapX;
    float worldToHeightmapZ;

    glm::vec3 sceneDimensions;
    glm::vec3 minVertexValues;
    glm::vec3 maxVertexValues;
    

private:

	void updatePlayerPosition1Sa(Player * p, Camera* cam = NULL) const;
	void updatePlayerPosition5Sa(Player * p, Camera* cam = NULL) const;
	void updatePlayerHeadDirection(Player* p, Camera* cam = NULL) const;

	glm::vec2 getStateInCamSpace(glm::vec2 state, glm::vec3 playerPos, Camera* cam = NULL) const;
	void readBMP(const char* filename);


	void printLoadingStats();

	int nodes;
	int verts;
};

#endif
