#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H 

#include "Node.h"
#include "sgct.h"

class Transformation : public Node{

public:
	Transformation();
	virtual ~Transformation();

	glm::mat4 getMatrix() const;


protected:

	glm::mat4 matrix;

};
#endif