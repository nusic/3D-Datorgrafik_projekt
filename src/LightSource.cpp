#include "LightSource.h"

LightSource::LightSource(double x, double y, double z, std::string _shaderName){

	LightSource::position.push_back(glm::vec3(x, y, z));
	LightSource::color.push_back(glm::vec3(1,1,1));
	LightSource::direction.push_back(glm::vec3(5,1,5));
	LightSource::intensity.push_back(50);
	LightSource::spread.push_back(1);
	LightSource::directional.push_back(true);

	index = LightSource::position.size() - 1;

	shaderName = _shaderName;

	bindVariables();
}

LightSource::~LightSource(){
	//Ta bort en ljuskälla.
}

std::string LightSource::shaderName = "SimpleColor";

std::vector<glm::vec3> LightSource::position;
std::vector<glm::vec3> LightSource::color;
std::vector<glm::vec3> LightSource::direction;
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
	LightSource::position[index] = glm::vec3(x, y, z);
}

void LightSource::setColor(double r, double g, double b){
	LightSource::color[index] = glm::vec3(r, g, b);
}

void LightSource::setDirection(double x, double y, double z){
	LightSource::direction[index] = glm::vec3(x, y, z);
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
	return &(LightSource::position[0].x);
}

float* LightSource::getColorArray(){
	return &(LightSource::color[0].x);
}

float* LightSource::getDirectionArray(){
	return &(LightSource::direction[0].x);
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
	return position.size();
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

