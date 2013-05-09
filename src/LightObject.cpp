#include "LightObject.h"

LightObject::LightObject(double x, double y, double z, float Scale, float _phi):
GameObject(x, y, z, Scale, _phi){

}

void LightObject::setPosition(double x, double y, double z){
	//GameObject::setPosition(x, y, z);
	light->setPosition(x, y, z);
}

void LightObject::setDirection(float phi, float theta){
	GameObject::setDirection(phi, theta);
	light->setDirection(
		sin(phi)*cos(theta), 
		sin(phi)*sin(theta),
		cos(theta));
}

void LightObject::setDirection(double x, double y, double z, double parentPhi){
	//WARNING
	//THIS METHOD DOESN'T CARE TO CALC THETA
	GameObject::setDirection(180.0f / 3.141592 * glm::atan(z/-x) - parentPhi, 0);
	light->setDirection(x, y, z);
}

void LightObject::updateLightOrientation(glm::mat4 parentLocalModelMatrix){
	glm::mat4 thisM = parentLocalModelMatrix;// * localModelMatrix;
	glm::vec4 pos = thisM * glm::vec4(light->getPosition(), 1.0f);
	glm::vec4 dir = thisM * glm::vec4(light->getDirection(), 0.0f);
	light->setPosition(pos.x, pos.y, pos.z);
	light->setDirection(dir.x, dir.y, dir.z);
}
