#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Node.h"
#include "Transformation.h"
#include "Model.h"
#include "sgct.h"

class GameObject{
public:
	GameObject(double x = 0, double y = 0, double z = 0, float scale = 1.0f, float _phi = 0);
	~GameObject();

	//POSITIONS
	void setPosition(double x, double y, double z = 0);
	void setYPosition(float y);
	void setDirection(float phi = 0, float theta = 0);
	void setScale(float s);
	void setScale(float xs, float ys, float zs);

	glm::vec3 getPosition();
	void incrementPosition(double dx, double dy, double dz);
	void incrementPositionAndTurnTo(double dx, double dy, double dz);



	//VELOCITIES
	void setVelocity(double dx = 0, double dy = 0, double d = 0);
	void setAngleVel(float _dPhi, float dTheta);

	glm::vec3 getVelocity();

	void incrementAngleVel();
	void incrementAngleVel(float _dPhi, float _dTheta);

	float getSpeed() const;

	//call this function every frame when final
	//position, direction, and Scale is set.
	void update(float dt);
	void updateMatrix();

	Node* getSceneGraphBranch() const;
	Model* getMainModel() const;

	Translation* 	translationNode;
	Rotation* 		rotationNode;
	Scaling*		scaleNode;
	Model*			modelNode;

protected:

	float speed;

private:

	glm::vec3 position;
	glm::vec3 scale;
	float phi, theta;

	glm::vec3 velocity;
	float dPhi, dTheta;
	
	

};

#endif

