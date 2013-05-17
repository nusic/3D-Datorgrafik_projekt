#include "GameObject.h"

GameObject::GameObject(double x, double y, double z, float s, float phi){

	translationNode = new Translation(x,y,z);
	rotationNode = new Rotation(translationNode, phi, glm::vec3(0.0f, 1.0f, 0.0f));
	scaleNode = new Scaling(rotationNode, s, s, s);
	modelNode = new Model(scaleNode, new ModelMesh("data/meshes/suzanne.obj"), "SimpleTexture2", "SimpleColor");

	setPosition(x, y, z);
	setScale(s);
	setDirection(phi, 0.0f);
	setVelocity(0.0f, 0.0f, 0.0f);

	speed = 5.0f;
	turnSpeed = 5.0f;

}

GameObject::GameObject(const char* modelPath){

	translationNode = new Translation(0,0,0);
	rotationNode = new Rotation(translationNode, phi, glm::vec3(0.0f, 1.0f, 0.0f));
	scaleNode = new Scaling(rotationNode, 1.0f, 1.0f, 1.0f);
	modelNode = new Model(scaleNode, new ModelMesh(modelPath), "SimpleTexture2", "SimpleColor");

	setPosition(0, 0, 0);
	setScale(1.0f);
	setDirection(0, 0.0f);
	setVelocity(0.0f, 0.0f, 0.0f);

	speed = 5.0f;
	turnSpeed = 5.0f;

}

GameObject::~GameObject(){

};


void GameObject::setPosition(double x, double y, double z){
	position.x = x;
	position.y = y;
	position.z = z;
}

void GameObject::setYPosition(float y){
    position.y = y;
}

void GameObject::setDirection(float _phi, float _theta){
	phi = _phi;
	theta = _theta;
}

void GameObject::setScale(float s){
	scale.x = scale.y = scale.z = s;
}

void GameObject::setScale(float xs, float ys, float zs){
	scale.x = xs;
	scale.y = ys;
	scale.z = zs;
}

void GameObject::setVelocity(double dx, double dy, double dz){
	velocity.x = dx;
	velocity.y = dy;
	velocity.z = dz;
}

void GameObject::setAngleVel(float _dPhi, float _dTheta){
	dPhi = _dPhi;
	dTheta = _dTheta;
}




const glm::vec3& GameObject::getPosition() const{
	return position;
}

const glm::vec3& GameObject::getVelocity() const{
	return velocity;
}

float GameObject::getSpeed() const{
	return speed;
}

float GameObject::getAvgScale() const{
	return (scaleNode->getMatrix()[0][0] +
			scaleNode->getMatrix()[1][1] +
			scaleNode->getMatrix()[2][2]) / 3.0f;
}

float GameObject::getBaseRadius() const{
	return getAvgScale()*modelNode->getMesh()->getRadius();
}



float GameObject::getPhi() const{
	return phi;
}



Node* GameObject::getSceneGraphBranch() const{
	return translationNode;
}

Model* GameObject::getMainModel() const{
	return modelNode;
}


void GameObject::update(float dt){
	position.x += velocity.x * dt * speed;
	position.y += velocity.y * dt * speed;
	position.z += velocity.z * dt * speed;

	phi += dPhi * dt * turnSpeed;
	if(phi < -180.0f)
		phi+=360.0f;
	else if(phi > 180.0f)
		phi-= 360.0f;

	theta += dTheta * dt * turnSpeed;
	if(theta < -180.0f)
		theta+=360.0f;
	else if(theta > 180.0f)
		theta-= 360.0f;

	translationNode->setTranslation(position.x, position.y, position.z);
	rotationNode->setRotation(phi);
	scaleNode->setScaling(scale.x, scale.y, scale.z);
}

