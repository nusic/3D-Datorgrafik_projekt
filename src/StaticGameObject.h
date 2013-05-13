#ifndef STATICGAMEOBJECT_H
#define STATICGAMEOBJECT_H 

#include "Node.h"
#include "Transformation.h"
#include "Model.h"

class StaticGameObject{

public:
	StaticGameObject(float x = 0, float y = 0, float z = 0, float scale = 1.0f, float _phi = 0, float _theta = 0);
	StaticGameObject(std::string objfile, std::string texture, std::string shader);
	~StaticGameObject();

	void setYPosition(float y);
	void setPosition(float x, float y, float z);
	void setSize(float x, float y, float z);
	void setRotation(float phi, float theta = 0);

	Node* getSceneGraphBranch() const;
	
	Model* modelNode;

private:

	Transformation* transformationNode;
	
};
#endif
