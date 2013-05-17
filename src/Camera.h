#ifndef CAMERA_H
#define CAMERA_H

#include "sgct.h"

class Camera{
public:
	Camera(double x, double y, double z);
	~Camera();


	void bindVariables();

	void setPosition(double x, double y, double z);
	void setVelocity(double dx, double dy, double dz);
	void setLookAt(double x, double y, double z);

	void incrementPosition(float dt);
	void incrementPosition(double dx, double dy, double dz, float dt);

	void calcMatrices();

	glm::mat4 getViewMatrix() const;
	glm::mat4 getPerspectiveMatrix() const;

	glm::vec3 getLookAt();
	glm::vec3 getPosition();

private:

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 lookAt;
	glm::vec3 up;

	float fov;
	float aspect;
	float zNearClipping;
	float zFarClipping;

	glm::mat4 viewMatrix;
	glm::mat4 perspectiveMatrix;
	
};

#endif