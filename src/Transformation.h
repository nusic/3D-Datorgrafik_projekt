#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H 

#include "Node.h"
#include "sgct.h"

class Transformation : public Node{
public:
	Transformation(Node * _parent = NULL);
	virtual ~Transformation();

	glm::mat4 getMatrix() const;

	virtual void draw(glm::mat4 &P, glm::mat4 &V, glm::mat4 &parentModelMatrix);

protected:
	friend class StaticGameObject;
	glm::mat4 matrix;
};







class Scaling : public Transformation {
public:
	Scaling(float sx, float sy, float sz);
	Scaling(Node * _parent, float sx, float sy, float sz);
	virtual ~Scaling();

	void setScaling(float s);
	void setScaling(float sx, float sy, float sz);
	glm::vec3 getScaling() const;
};






class Rotation : public Transformation{
public:
	Rotation(float angle, glm::vec3 axis);
	Rotation(Node * _parent, float angle, glm::vec3 axis);
	virtual ~Rotation();

	void setRotation(float angle, glm::vec3 axis);
};






class Translation : public Transformation{
public:
	Translation(float x, float y, float z);
	Translation(Node * _parent, float x, float y, float z);
	virtual ~Translation();

	void setTranslation(float x, float y, float z);
	glm::vec3 getTranslation() const;
};


#endif