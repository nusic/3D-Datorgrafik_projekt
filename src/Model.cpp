#include "Model.h"


Model::Model(
	ModelMesh* _mesh,
	glm::mat4 M,
	std::string _textureName,
	std::string _shaderName){
	
	mesh = _mesh;
	if(!mesh)
		std::cout << "WARNING: MODEL WITH NULL MESH CREATED!!!!!" << std::endl;
	setShader(_shaderName);
	setTexture(_textureName);
	setModelMatrix(M);

	std::cout << "created Model" << std::endl;
}

void Model::setTexture(std::string _textureName){
	if(!(texture = sgct::TextureManager::Instance()->getTextureByName(_textureName)))
		std::cout << "WARNING: setTexture: " << _textureName << " failed!!!!!" << std::endl;
}

void Model::setShader(std::string _shaderName){

	shaderName = _shaderName;

	sgct::ShaderManager::Instance()->bindShader(shaderName);

	//The handle for the vertex data
	vertexPositionID = sgct::ShaderManager::Instance()->getShader(shaderName).getAttribLocation("vertexPosition");
	vertexNormalID = sgct::ShaderManager::Instance()->getShader(shaderName).getAttribLocation("vertexNormal");
	vertexUVID = sgct::ShaderManager::Instance()->getShader(shaderName).getAttribLocation("vertexUV");
	//The handle for the MVP-matrix
	modelMatrixID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("MVP");
	//The handler for the texture sampler
	textureID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("textureSampler");

	sgct::ShaderManager::Instance()->unBindShader();
}

void Model::setModelMatrix(glm::mat4 _modelMatrix){
	modelMatrix = _modelMatrix;
	//modelMatrixID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("MVP");
}

bool Model::hasMesh() const{
    return (mesh != NULL);
}

float angle = 0.0f;

void Model::drawModel(glm::mat4 MVP){

	//Use the shader	
	assert(sgct::ShaderManager::Instance()->bindShader(shaderName));

	//En modells position i världen beror på vart dess "parent" befann sig.
	//Tänk på hur stegu snackaded om scengrafer. Model-matrisen talar om
	//hur den här modellen befinner sig i för hållande till sin parent.
	//För att få denna modells position i världen multiplicerar vi med vår
	//parents MVP matris med vår egen model-matrix. På så sätt vet vi hur vi ska
	//rita ut oss. Resultatet, "thisMVP", skickar vi vidare till våra children
	//för att de ska veta dess position i världen.

	glm::mat4 thisMVP = MVP * modelMatrix;

	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &thisMVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set our "textureSampler" sampler to user Texture Unit 0
	glUniform1i(textureID, 0);

	//Attribute the vertices buffer
	glEnableVertexAttribArray(vertexPositionID);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glVertexAttribPointer(
		vertexPositionID, // The attribute we want to configure (vertexShaderID)
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	//Attribute the normal buffer
	glEnableVertexAttribArray(vertexUVID);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->uvBuffer);
	glVertexAttribPointer(
		vertexUVID, // The attribute we want to configure (uvShaderID)
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	//Attribute the normal buffer
	glEnableVertexAttribArray(vertexNormalID);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->normalBuffer);
	glVertexAttribPointer(
		vertexNormalID, // The attribute we want to configure (normalShaderID)
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangles!
	glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.size());

	glDisableVertexAttribArray(vertexPositionID);
	glDisableVertexAttribArray(vertexUVID);
	glDisableVertexAttribArray(vertexNormalID);

	sgct::ShaderManager::Instance()->unBindShader();

	for(int i = 0; i<children.size(); ++i){
		children[i].drawModel(thisMVP);
	}
}
