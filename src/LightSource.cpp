#include "LightSource.h"
#include "sgct.h"

LightSource::LightSource(
	double _x = 0,
	double _y = 0,
	double _z = 0,
	std::string _shaderName = "SimpleColor"){

	position = glm::vec3(_x, _y, _z);
	color = glm::vec3(1, 1, 1);
	direction = glm::vec3(_x, _y, _z);
	spread = 1;

	directional = true;

	shaderName = _shaderName;

	bindVariables();
}

LightSource::~LightSource(){
	
}

void LightSource::bindVariables(){
	//Vi borde på något sätt binda flera stycken ljuskällor,
	//variablerna kan ju inte ha samma namn för alla, så detta är egentligen dåligt.

	lightPositionID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("lightPosition_worldSpace");
	lightColorID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("lightColor");
	lightDirectionID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("lightDirection_worldSpace");
	lightSpreadID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("lightSpread");
	directionalID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("directional");
}
