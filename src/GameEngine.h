#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>
#include <ctime>

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


	Scene * scene;
	Camera * camera;

	GLuint currentTimeId;
	GLuint globalRandomId;

	//Variables to share across cluster
	double currentTime;
	double globalRandom;
};

#endif
