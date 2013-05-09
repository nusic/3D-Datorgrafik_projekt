#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H 

#include "Node.h"
#include "sgct.h"

class Transformation : public Node{

public:
	Transformation();
	virtual ~Transformation();

	glm::mat4 getMatrix() const;

	virtual void draw(glm::mat4 &P, glm::mat4 &V, glm::mat4 &parentModelMatrix);

protected:

	glm::mat4 matrix;

};
#endif