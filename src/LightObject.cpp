#include "LightObject.h"

LightObject::LightObject(double x, double y, double z, float Scale, float _phi):
GameObject(x, y, z, Scale, _phi){

}

void LightObject::setPosition(double x, double y, double z){
	GameObject::setPosition(x, y, z);
	light->setPosition(x, y, z);
}

void LightObject::setDirection(float phi, float theta){
	GameObject::setDirection(phi, theta);
	light->setDirection(
		sin(phi)*cos(theta), 
		sin(phi)*sin(theta),
		cos(theta));
}
