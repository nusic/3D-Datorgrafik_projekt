#include "Model.h"
#include "Scene.h"


Model::Model(ModelMesh* _mesh, std::string _textureName, std::string _shaderName){
	setMesh(_mesh);
	setShader(_shaderName);
	setTexture(_textureName);
}

Model::Model(Node* _parent, ModelMesh* _mesh, std::string _textureName, std::string _shaderName):
Node(_parent){
	setMesh(_mesh);
	setShader(_shaderName);
	setTexture(_textureName);
}


Model::~Model(){
	delete mesh;
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

glm::vec3 Model::getMaxVertexValues(){
    glm::vec3 maxValues = mesh->vertices[0];
    for(int i = 1; i<mesh->vertices.size(); ++i){
        if(mesh->vertices[i].x > maxValues.x) maxValues.x = mesh->vertices[i].x;
        if(mesh->vertices[i].y > maxValues.y) maxValues.y = mesh->vertices[i].y;
        if(mesh->vertices[i].z > maxValues.z) maxValues.z = mesh->vertices[i].z;
    }
    return maxValues;
}

glm::vec3 Model::getMinVertexValues(){
    glm::vec3 minValues = mesh->vertices[0];
    for(int i = 1; i<mesh->vertices.size(); ++i){
        if(mesh->vertices[i].x < minValues.x) minValues.x = mesh->vertices[i].x;
        if(mesh->vertices[i].y < minValues.y) minValues.y = mesh->vertices[i].y;
        if(mesh->vertices[i].z < minValues.z) minValues.z = mesh->vertices[i].z;
    }
    return minValues;
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

	//Don't use currently bound shader anymore
	sgct::ShaderManager::Instance()->unBindShader();
}

bool Model::hasMesh() const{
    return (mesh != NULL);
}

void Model::draw(glm::mat4 &P, glm::mat4 &V, glm::mat4 &M){
	drawModel(P, V, M);
	Node::draw(P, V, M);
}

void Model::drawModel(glm::mat4 P, glm::mat4 V, glm::mat4 M){

	//Use the shader
	assert(sgct::ShaderManager::Instance()->bindShader(shaderName));

	//Calculate matrices necessary for shader
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

}
