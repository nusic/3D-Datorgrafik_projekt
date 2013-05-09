#ifndef ROTATION_H
#define ROTATION_H 

#include "Transformation.h"
#include "sgct.h"

class Rotation : public Transformation{

public:
	Rotation(float angle, glm::vec3 axis);
	virtual ~Rotation();

	void setRotation(float angle, glm::vec3 axis);

};
#endif