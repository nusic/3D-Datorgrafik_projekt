#include "LightSource.h"


LightSource::LightSource(double x, double y, double z, std::string _shaderName){
	setStandardValues();
	position = glm::vec3(x,y,z);
	shaderName = _shaderName;

	//This should only be done once
	if (index == 0){
		bindVariables();
	}
	if(!initShadowMapBuffers()){
		std::cout << "Unable to initialize shadow map buffer!" << std::endl;
	}
}

LightSource::LightSource(Node* _parent, double x, double y, double z, std::string _shaderName):
Node(_parent){
	setStandardValues();
	position = glm::vec3(x,y,z);
	shaderName = _shaderName;

	//This should only be done once
	if (index == 0){
		bindVariables();
	}
	if(!initShadowMapBuffers()){
		std::cout << "Unable to initialize shadow map buffer!" << std::endl;
	}
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

GLuint LightSource::depthMatrixID;
GLuint LightSource::depth_vertexPosition_modelspaceID;

GLuint LightSource::depthBiasID;

std::vector<GLuint> LightSource::FBO;
std::vector<GLuint> LightSource::depthTexture;


void LightSource::setStandardValues(){
	index = LightSource::worldPosition.size();
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	direction = glm::vec3(0.0f, 0.0f, 1.0f);

	LightSource::worldPosition.push_back(glm::vec3(0, 0, index));
	LightSource::worldDirection.push_back(glm::vec3(5,1,5));
	LightSource::color.push_back(glm::vec3(1,1,1));
	LightSource::intensity.push_back(50);
	LightSource::spread.push_back(1);
	LightSource::directional.push_back(true);
}


LightSource::~LightSource(){
	std::cout << "NÄ MEN NU FÅR DU SKÄRPA DIG, TA INTE BORT EN LIGHTSOURCE!!" << std::endl <<
		"NU BLIR DET MÖRKT RAGNAR!!" << std::endl;
}


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

const glm::vec3& LightSource::getPosition() const{
	return position;
}

const glm::vec3& LightSource::getDirection() const{
	return direction;
}

const glm::mat4 LightSource::getVP() const{
	glm::mat4 V = glm::lookAt(worldPosition[index], worldPosition[index] + worldDirection[index], glm::vec3(0,1,0));
	glm::mat4 P = glm::perspective(90.0f, 1.0f, 1.0f, 200.0f);

	return P * V;
}

glm::mat4 LightSource::getVPFromIndex(int _index){
	glm::mat4 V = glm::lookAt(worldPosition[_index], worldPosition[_index] + worldDirection[_index], glm::vec3(0,1,0));
	glm::mat4 P = glm::perspective(90.0f, 1.0f, 1.0f, 200.0f);

	return P * V;
}

const glm::vec3& LightSource::getWorldPosition() const{
	return LightSource::worldPosition[index];
}

const glm::vec3& LightSource::getWorldDirection() const{
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



void LightSource::renderToScreen(glm::mat4 &P, glm::mat4 &V, glm::mat4 &M){

	glm::vec4 worldPos = M * glm::vec4(position, 1);
	glm::vec4 worldDir = M * glm::vec4(direction, 0);
	//printf("worldDir:  x=%f y=%f z=%f  \n", worldDir.x, worldDir.y, worldDir.z);
	setWorldPosition(worldPos.x, worldPos.y, worldPos.z);
	setWorldDirection(worldDir.x, worldDir.y, worldDir.z);

	Node::renderToScreen(P, V, M);
}

void LightSource::renderToDepthBuffer(glm::mat4 &VP, glm::mat4 &M){
	glm::vec4 worldPos = M * glm::vec4(position, 1);
	glm::vec4 worldDir = M * glm::vec4(direction, 0);
	//printf("worldDir:  x=%f y=%f z=%f  \n", worldDir.x, worldDir.y, worldDir.z);
	setWorldPosition(worldPos.x, worldPos.y, worldPos.z);
	setWorldDirection(worldDir.x, worldDir.y, worldDir.z);

	Node::renderToDepthBuffer(VP, M);
}




bool LightSource::initShadowMapBuffers(){
	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	GLuint frameBufferObj = 0;
	glGenFramebuffers(1, &frameBufferObj);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObj);

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	GLuint depthTex = 0;
	glGenTextures(1, &depthTex);
	glBindTexture(GL_TEXTURE_2D, depthTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, SHADOW_MAP_RESOLUTION, SHADOW_MAP_RESOLUTION, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	// Inte säker på vad denna gjorde men den verkar inte behövas (låter den vara kommenterad dock)
	//glTexParameteri( shadowMapID , GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB );
		 
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTex, 0);

	// No color output in the bound framebuffer, only depth.
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	// Always check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		std::cout << "FRAMEBUFFER IS NOT OK!!!" << std::endl;
		return false;
	}

	FBO.push_back(frameBufferObj);
	depthTexture.push_back(depthTex);
	return true;
}

void LightSource::bindVariables(){
	sgct::ShaderManager::Instance()->bindShader( "SimpleColor" );
	lightPositionID = 	sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("lightPosition_worldSpace");
	lightColorID = 		sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("lightColor");
	lightDirectionID = 	sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("lightDirection_worldSpace");
	lightIntensityID = 	sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("lightIntensity");
	lightSpreadID = 	sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("lightSpread");
	directionalID = 	sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("directional");
	numberOfLightsID = 	sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("numberOfLights");
	sgct::ShaderManager::Instance()->unBindShader();

	depthBiasID = 		sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("depthBiasMVP");
	//The last two will be used when rendering to the depth-buffer
	depthMatrixID = 	sgct::ShaderManager::Instance()->getShader("depthProgram").getUniformLocation("depthMVP");
	depth_vertexPosition_modelspaceID = sgct::ShaderManager::Instance()->getShader("depthProgram").getAttribLocation("vertexPosition_modelspace");
}

