#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Node.h"
#include "Transformation.h"
#include "Model.h"
#include "sgct.h"

class GameObject{
public:
	GameObject(double x = 0, double y = 0, double z = 0, float Scale = 1.0f, float _phi = 0);
	~GameObject();

	void setPosition(double x, double y, double z = 0);
	void setDirection(float phi = 0, float theta = 0);
	void setScale(float s);
	void setScale(float xs, float ys, float zs);

	void incrementPosition(double dx, double dy, double dz);
	void incrementPositionAndTurnTo(double dx, double dy, double dz);


	//call this function every frame when final
	//position, direction, and Scale is set.
	void updateMatrix();

	Node* getSceneGraphBranch() const;
	Model* getMainModel() const;

protected:

	glm::vec3 position;
	glm::vec3 scale;
	float phi, theta;


private:

	Translation* 	translationNode;
	Rotation* 		rotationNode;
	Scaling*		scaleNode;
	Model*			modelNode;

};

#endif

