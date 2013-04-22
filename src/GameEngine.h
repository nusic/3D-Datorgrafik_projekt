#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>

#include "sgct.h"
#include "Scene.h"
#include "GameObject.h"


class GameEngine{
public:
	GameEngine();
	~GameEngine();

	void draw();
	void preSync();
	void initOGL();
	void encode();
	void decode();


	Scene * scene;
};

#endif