#include "LightSource.h"

LightSource::LightSource(double x, double y, double z, std::string _shaderName){

	position = glm::vec3(0.0f, 0.0f, 0.0f);
	direction = glm::vec3(1.0f, 0.0f, 1.0f);

	LightSource::worldPosition.push_back(glm::vec3(x, y, z));
	LightSource::worldDirection.push_back(glm::vec3(5,1,5));
	LightSource::color.push_back(glm::vec3(1,1,1));
	LightSource::intensity.push_back(50);
	LightSource::spread.push_back(1);
	LightSource::directional.push_back(true);

	index = LightSource::worldPosition.size() - 1;

	shaderName = _shaderName;

	bindVariables();
}

LightSource::~LightSource(){
	std::cout << "NÄ MEN NU FÅR DU SKÄRPA DIG, TA INTE BORT EN LIGHTSOURCE!!" << std::endl <<
		"NU BLIR DET MÖRKT RAGNAR!!" << std::endl;
}

void LightSource::draw(glm::mat4 &P, glm::mat4 &V, glm::mat4 &M){
	glm::vec4 worldPos = M * glm::vec4(position, 1);
	glm::vec4 worldDir = M * glm::vec4(direction, 0);
	//printf("worldDir:  x=%f y=%f z=%f  \n", worldDir.x, worldDir.y, worldDir.z);
	setWorldPosition(worldPos.x, worldPos.y, worldPos.z);
	setWorldDirection(worldDir.x, worldDir.y, worldDir.z);
	Node::draw(P, V, M);
}

std::string LightSource::shaderName = "SimpleColor";

std::vector<glm::vec3> LightSource::worldPosition;
std::vector<glm::vec3> LightSource::color;
std::vector<glm::vec3> LightSource::worldDirection;
std::vector<float> LightSource::intensity;
std::vector<float> LightSource::spread;
std::vector<int> LightSource::directional;

GLuint LightSource::lightPositionID;
GLuint LightSource::lightColorID;
GLuint LightSource::lightDirectionID;
GLuint LightSource::lightIntensityID;
GLuint LightSource::lightSpreadID;
GLuint LightSource::directionalID;
GLuint LightSource::numberOfLightsID;


void LightSource::setPosition(double x, double y, double z){
	position.x = x;
	position.y = y;
	position.z = z;
}

void LightSource::setDirection(double x, double y, double z){
	direction.x = x;
	direction.y = y;
	direction.z = z;
}

glm::vec3 LightSource::getPosition(){
	return position;
}

glm::vec3 LightSource::getDirection(){
	return direction;
}


glm::vec3 LightSource::getWorldPosition(){
	return LightSource::worldPosition[index];
}

glm::vec3 LightSource::getWorldDirection(){
	return LightSource::worldDirection[index];
}

void LightSource::setWorldPosition(double x, double y, double z){
	LightSource::worldPosition[index] = glm::vec3(x, y, z);
}

void LightSource::setWorldDirection(double x, double y, double z){
	LightSource::worldDirection[index] = glm::vec3(x, y, z);
}

void LightSource::setColor(double r, double g, double b){
	LightSource::color[index] = glm::vec3(r, g, b);
}

void LightSource::setIntensity(float i){
	LightSource::intensity[index] = i;
}

void LightSource::setSpread(float s){
	LightSource::spread[index] = s;
}

void LightSource::setDirectional(bool d){
	LightSource::directional[index] = d;
}


float* LightSource::getPositionArray(){
	return &(LightSource::worldPosition[0].x);
}

float* LightSource::getColorArray(){
	return &(LightSource::color[0].x);
}

float* LightSource::getDirectionArray(){
	return &(LightSource::worldDirection[0].x);
}

float* LightSource::getIntensityArray(){
	return &LightSource::intensity[0];
}

float* LightSource::getSpreadArray(){
	return &LightSource::spread[0];
}

int* LightSource::getDirectionalArray(){
	return &LightSource::directional[0];
}

unsigned short LightSource::getNumberOfLightSources(){
	return worldPosition.size();
}

void LightSource::bindVariables(){
	sgct::ShaderManager::Instance()->bindShader( "SimpleColor" );
	LightSource::lightPositionID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("lightPosition_worldSpace");
	LightSource::lightColorID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("lightColor");
	LightSource::lightDirectionID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("lightDirection_worldSpace");
	LightSource::lightIntensityID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("lightIntensity");
	LightSource::lightSpreadID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("lightSpread");
	LightSource::directionalID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("directional");
	LightSource::numberOfLightsID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("numberOfLights");
	sgct::ShaderManager::Instance()->unBindShader();
}

