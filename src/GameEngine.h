#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>
#include "Model.h"
#include "GameObject.h"


class GameEngine{
public:
	GameEngine();
	~GameEngine();

	void drawScene();
	void preSync();
	void initOGL();
	void encode();
	void decode();


	std::vector<GameObject> scene;
};

#endif