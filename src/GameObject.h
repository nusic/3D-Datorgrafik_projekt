#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Node.h"
#include "Transformation.h"
#include "Model.h"
#include "sgct.h"

class GameObject{
public:
	//GameObject(double x = 0, double y = 0, double z = 0, float scale = 1.0f, float _phi = 0);
	GameObject(const char* modelPath = "suzanne", const char* texture = "SimpleTexture2", const char* shaderName = "SimpleColor");
	~GameObject();

	void setPosition(double x, double y, double z);
	void setYPosition(float y);
	void setDirection(float phi, float theta = 0);
	void setScale(float s);
	void setScale(float xs, float ys, float zs);
	void setVelocity(double dx, double dy, double d);
	void setAngleVel(float _dPhi, float dTheta = 0);

	const glm::vec3& getPosition() const;
	const glm::vec3& getVelocity() const;
	float getSpeed() const;
	float getBaseRadius() const;
	float getAvgScale() const;
	float getPhi() const;

	Node* getSceneGraphBranch() const;
	Model* getMainModel() const;

	void update(float dt);

protected:
    friend class Player;
    friend class Character;

    Translation* 	translationNode;
	Rotation* 		rotationNode;
	Scaling*		scaleNode;
	Model*			modelNode;

    float speed;
	float turnSpeed;

private:

	glm::vec3 scale;
	glm::vec3 position;
	glm::vec3 velocity;
	float phi, theta;
	float dPhi, dTheta;

};

#endif

