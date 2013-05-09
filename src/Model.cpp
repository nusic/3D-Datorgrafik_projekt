#include "Model.h"


Model::Model(ModelMesh* _mesh, glm::mat4 _localModelMatrix, std::string _textureName, std::string _shaderName){
	setMesh(_mesh);
	setShader(_shaderName);
	setTexture(_textureName);
	setLocalModelMatrix(_localModelMatrix);
}

Model::~Model(){
	
}

void Model::setTexture(std::string _textureName){
	if(!(texture = sgct::TextureManager::Instance()->getTextureByName(_textureName)))
		std::cout << "WARNING: setTexture: " << _textureName << " failed!!!!!" << std::endl;
}

void Model::setMesh(ModelMesh* _mesh){
	mesh = _mesh;
	if(!mesh)
		std::cout << "WARNING: MODEL WITH NULL MESH CREATED!!!!!" << std::endl;
}

void Model::setShader(std::string _shaderName){
	shaderName = _shaderName;

	//Use the shader
	assert(sgct::ShaderManager::Instance()->bindShader(shaderName));

	//Get handles for vertex data
	vertexPositionID = 				sgct::ShaderManager::Instance()->getShader(shaderName).getAttribLocation("vertexPosition");
	vertexNormalID = 				sgct::ShaderManager::Instance()->getShader(shaderName).getAttribLocation("vertexNormal");
	vertexUVID = 					sgct::ShaderManager::Instance()->getShader(shaderName).getAttribLocation("vertexUV");

	//Get handles for the matrix data
	modelMatrixID = 				sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("M");
	viewMatrixID = 					sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("V");
	modelViewMatrixID = 			sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("MV");
	modelViewPerspectiveMatrixID = 	sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("MVP");

	//Get handle for the texture sampler
	textureID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("textureSampler");

	ShadowMap::depthBiasID = sgct::ShaderManager::Instance()->getShader( "SimpleColor").getUniformLocation( "depthBiasMVP" );
	ShadowMap::shadowMapID = sgct::ShaderManager::Instance()->getShader( "SimpleColor").getUniformLocation( "shadowMap" );

	//Don't use currently bound shader anymore
	sgct::ShaderManager::Instance()->unBindShader();



}

void Model::setLocalModelMatrix(glm::mat4 _localModelMatrix){
	localModelMatrix = _localModelMatrix;
}

bool Model::hasMesh() const{
    return (mesh != NULL);
}



void Model::drawModel(glm::mat4 P, glm::mat4 V, glm::mat4 parentModelMatrix){

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//Use the shader
	assert(sgct::ShaderManager::Instance()->bindShader(shaderName));

	//Calculate matrices necessary for shader
	glm::mat4 M = parentModelMatrix * localModelMatrix;
	glm::mat4 MV = V * M;
	glm::mat4 MVP = P * V * M;
	
	//Bind matrices to shader
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &V[0][0]);
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &M[0][0]);
	glUniformMatrix4fv(modelViewMatrixID, 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(modelViewPerspectiveMatrixID, 1, GL_FALSE, &MVP[0][0]);


	//Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	//Set our "textureSampler" sampler to user Texture Unit 0
	glUniform1i(textureID, 0);











	glm::mat4 depthModelMatrix = parentModelMatrix * localModelMatrix;

	glm::vec3 lightDir = - glm::vec3(LightSource::getDirectionArray()[0],LightSource::getDirectionArray()[1],
		LightSource::getDirectionArray()[2]);
	glm::vec3 lightPos(LightSource::getPositionArray()[0],LightSource::getPositionArray()[1],
		LightSource::getPositionArray()[2]);

	// Compute the MVP matrix from the light's point of view
	//glm::mat4 depthProjectionMatrix = glm::ortho<float>(-15,15,-15,15,-15,30);
	glm::mat4 depthViewMatrix = glm::lookAt(lightPos, lightPos - lightDir, glm::vec3(0,1,0));
	// or, for spot light :
	glm::mat4 depthProjectionMatrix = glm::perspective(45.0f, 1.0f, 1.0f, 30.0f);
	//glm::mat4 depthViewMatrix = glm::lookAt(lightPos, lightPos - lightDir, glm::vec3(0,1,0));

	glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;


	glm::mat4 biasMatrix(
		0.5, 0.0, 0.0, 0.0, 
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);

	glm::mat4 depthBiasMVP = biasMatrix*depthMVP;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(ShadowMap::depthBiasID, 1, GL_FALSE, &depthBiasMVP[0][0]);






	//Depth texture sampler
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, ShadowMap::depthTexture);
	glUniform1i(ShadowMap::shadowMapID, 1);


	//Lightsources data
	int numOfLightSources = LightSource::getNumberOfLightSources();
	glUniform1i(	LightSource::numberOfLightsID,	numOfLightSources);
	glUniform3fv(	LightSource::lightPositionID,	numOfLightSources, LightSource::getPositionArray());
	glUniform3fv(	LightSource::lightColorID,		numOfLightSources, LightSource::getColorArray());
	glUniform3fv(	LightSource::lightDirectionID,	numOfLightSources, LightSource::getDirectionArray());
	glUniform1fv(	LightSource::lightIntensityID,	numOfLightSources, LightSource::getIntensityArray());
	glUniform1fv(	LightSource::lightSpreadID,		numOfLightSources, LightSource::getSpreadArray());
	glUniform1iv(	LightSource::directionalID,		numOfLightSources, LightSource::getDirectionalArray());


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


	//Disable vertex arrays
	glDisableVertexAttribArray(vertexPositionID);
	glDisableVertexAttribArray(vertexUVID);
	glDisableVertexAttribArray(vertexNormalID);

	//Don't use the currently bound shader anymore
	sgct::ShaderManager::Instance()->unBindShader();


	//Draw our children
	for(int i = 0; i<children.size(); ++i){
		children[i]->drawModel(P, V, M);
	}
}

void Model::renderToFrameBuffer(glm::mat4 parentModelMatrix){


	// Use our shader
	assert(sgct::ShaderManager::Instance()->bindShader("depthProgram"));


	glm::mat4 depthModelMatrix = parentModelMatrix * localModelMatrix;

	glm::vec3 lightDir =  - glm::vec3(LightSource::getDirectionArray()[0], LightSource::getDirectionArray()[1],
		LightSource::getDirectionArray()[2]);
	glm::vec3 lightPos(LightSource::getPositionArray()[0],LightSource::getPositionArray()[1],
		LightSource::getPositionArray()[2]);

	// Compute the MVP matrix from the light's point of view
	//glm::mat4 depthProjectionMatrix = glm::ortho<float>(-15 ,15,-15,15,-15,30);
	glm::mat4 depthViewMatrix = glm::lookAt(lightPos, lightPos - lightDir, glm::vec3(0,1,0));
	// or, for spot light :
	glm::mat4 depthProjectionMatrix = glm::perspective(45.0f, 1.0f, 1.0f, 30.0f);
	//glm::mat4 depthViewMatrix = glm::lookAt(lightPos, lightPos - lightDir, glm::vec3(0,1,0));

	glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(ShadowMap::depthMatrixID, 1, GL_FALSE, &depthMVP[0][0]);




/*

	glm::vec3 lightInvDir = glm::vec3(0.5f,2,2);

	// Compute the MVP matrix from the light's point of view
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10,10,-10,10,-10,20);
	glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0,0,0), glm::vec3(0,1,0));
	// or, for spot light :
	//glm::vec3 lightPos(5, 20, 20);
	//glm::mat4 depthProjectionMatrix = glm::perspective<float>(45.0f, 1.0f, 2.0f, 50.0f);
	//glm::mat4 depthViewMatrix = glm::lookAt(lightPos, lightPos-lightInvDir, glm::vec3(0,1,0));

	glm::mat4 depthModelMatrix = glm::mat4(1.0);
	glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(ShadowMap::depthMatrixID, 1, GL_FALSE, &depthMVP[0][0]);

*/





	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(vertexPositionID);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glVertexAttribPointer(
		ShadowMap::depth_vertexPosition_modelspaceID,  // The attribute we want to configure
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangles!
	glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.size());

	glDisableVertexAttribArray(vertexPositionID);

	//Don't use the currently bound shader anymore
	sgct::ShaderManager::Instance()->unBindShader();

	
	//Render our children
	for(int i = 0; i<children.size(); ++i){
		children[i]->renderToFrameBuffer(depthModelMatrix);
	}


}
