#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Model.h";
#include "sgct.h"

class GameObject : public Model{
public:
	GameObject(double x = 0, double y = 0, float size = 1.0f, float _phi = 0);
	~GameObject();

	void setPosition(double x, double y);
	void setDirection(float phi, float theta);
	void setSize(float s);
	void setSize(float xs, float ys, float zs);

	//call this function every frame when final
	//position, direction, and size is set.
	void updateMatrix();


//protected:

	double x, y;
	float phi, theta;
	float xs, ys, zs;

private:



};

#endif

