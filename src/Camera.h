#ifndef CAMERA_H
#define CAMERA_H

#include "sgct.h"

class Camera{
public:
	Camera(double _x, double _y, double _z);
	~Camera();


	void bindVariables();

	void setPosition(double _x, double _y, double _z);
	void setVelocity(double _dx, double _dy, double _dz);
	void setLookAt(double _x, double _y, double _z);

	void incrementPosition();
	void incrementPosition(double _dx, double _dy, double _dz);

	void calcMatrices();

	glm::mat4 getViewMatrix() const;
	glm::mat4 getPerspectiveMatrix() const;

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