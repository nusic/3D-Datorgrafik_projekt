#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>

#include "sgct.h"
#include "Scene.h"
#include "Camera.h"
#include "GameObject.h"
#include "Player.h"

class GameEngine{
public:
	GameEngine();
	~GameEngine();

	void draw();
	void preSync();
	void initOGL();
	void encode();
	void decode();

	void keyCallback(int key, int action);
	void mouseButtonCallback(int key, int action);


	Scene * scene;
	Camera * camera;
};

#endif
