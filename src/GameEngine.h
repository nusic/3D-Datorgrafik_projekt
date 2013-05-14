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
	void preSync(float dt);
	void initOGL();
	void encode();
	void decode();


	Scene * scene;
	Camera * camera;
	Camera * camera2;
	
	GLuint currentTimeId;
	GLuint globalRandomId;

	//Variables to share across cluster
	double currentTime;
	double globalRandom;

	void swapRenderMode();

private:

	bool renderWireFrame;
	int defaultFBOindex;
	int getDefaultFBOindex() const;
};

#endif
