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

	void keyboardCallback(int key, int action);


	Scene * scene;

	GLuint currentTimeId;
	GLuint globalRandomId;

	//Variables to share across cluster
	double currentTime;
	double globalRandom;

	void toggleRenderMode();

private:

	bool renderWireFrame;

	#ifdef __APPLE__
        static const int DEFAULT_FBO_INDEX = 2;
	#else
        static const int DEFAULT_FBO_INDEX = 3;
	#endif

	int getDefaultFBOindex() const;
};

#endif
