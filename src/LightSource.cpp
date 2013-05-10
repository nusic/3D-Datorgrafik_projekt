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
	
	if(!initShadowMapBuffers(128)){
		std::cout << "Unable to initialize shadow map buffer!" << std::endl;
	}
	
}

LightSource::~LightSource(){
	std::cout << "NÄ MEN NU FÅR DU SKÄRPA DIG, TA INTE BORT EN LIGHTSOURCE!!" << std::endl <<
		"NU BLIR DET MÖRKT RAGNAR!!" << std::endl;
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

shadowMapData LightSource::shadowData;


bool LightSource::initShadowMapBuffers(int resolution){

	// Get a handle for our "MVP" uniform
	shadowData.depthMatrixID = sgct::ShaderManager::Instance()->getShader( "depthProgram").getUniformLocation( "depthMVP" );
	// Get a handle for our buffers
	shadowData.depth_vertexPosition_modelspaceID = sgct::ShaderManager::Instance()->getShader( "depthProgram").getAttribLocation( "vertexPosition_modelspace" );

	shadowData.depthBiasID = sgct::ShaderManager::Instance()->getShader( shaderName).getUniformLocation( "depthBiasMVP" );
	shadowData.shadowMapID = sgct::ShaderManager::Instance()->getShader( shaderName).getUniformLocation( "shadowMap" );

	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	shadowData.framebufferName = 0;
	glGenFramebuffers(1, &shadowData.framebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowData.framebufferName);

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	glGenTextures(1, &shadowData.depthTexture);
	glBindTexture(GL_TEXTURE_2D, shadowData.depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 128, 128, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	glTexParameteri( shadowData.shadowMapID , GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB );
		 
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowData.depthTexture, 0);

	// No color output in the bound framebuffer, only depth.
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	// Always check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		std::cout << "FRAMEBUFFER IS NOT OK!!!" << std::endl;
		return false;
	}

	return true;
}


glm::vec3 LightSource::getPosition(){
	return LightSource::position[index];
}

glm::vec3 LightSource::getDirection(){
	return LightSource::direction[index];
}

glm::mat4 LightSource::getVP(){
	glm::mat4 V = glm::lookAt(position[index], position[index] + direction[index], glm::vec3(0,1,0));
	glm::mat4 P = glm::perspective(45.0f, 1.0f, 1.0f, 30.0f);

	return P * V;
}

glm::mat4 LightSource::getVPFromIndex(int _index){
	glm::mat4 V = glm::lookAt(position[_index], position[_index] + direction[_index], glm::vec3(0,1,0));
	glm::mat4 P = glm::perspective(45.0f, 1.0f, 1.0f, 30.0f);

	return P * V;
}

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

