#ifndef STATICGAMEOBJECT_H
#define STATICGAMEOBJECT_H 

#include "Node.h"
#include "Transformation.h"
#include "Model.h"

class StaticGameObject{

public:
	StaticGameObject(float x = 0, float y = 0, float z = 0, float scale = 1.0f, float _phi = 0, float _theta = 0);
	~StaticGameObject();

	Transformation* transformationNode;
	Model* modelNode;
	
};
#endif
