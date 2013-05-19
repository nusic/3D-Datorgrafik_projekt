#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Node.h"
#include "sgct.h"

class Transformation : public Node{
public:
	Transformation(Node * _parent = NULL);
	virtual ~Transformation();

	const glm::mat4& getMatrix() const;

	virtual void renderToScreen(glm::mat4 &P, glm::mat4 &V, glm::mat4 &parentModelMatrix);
	virtual void renderToDepthBuffer(glm::mat4 &VP, glm::mat4 &M);

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
	Rotation(float angle, glm::vec3 _axis = glm::vec3(0.0f, 1.0f, 0.0f));
	Rotation(Node * _parent, float angle, glm::vec3 _axis = glm::vec3(0.0f, 1.0f, 0.0f));
	virtual ~Rotation();

    void setAxis(glm::vec3);
	void setRotation(float angle);

private:
    glm::vec3 axis;
};






class Translation : public Transformation{
public:
	Translation(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	Translation(Node * _parent, float x = 0.0f, float y = 0.0f, float z = 0.0f);
	virtual ~Translation();

	void setTranslation(float x, float y, float z);
	glm::vec3 getTranslation() const;
};


#endif
