#include "Model.h"
#include "Scene.h"


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

Model::~Model(){
	
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
	MVPMatrixID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("MVP");
	modelMatrixID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("M");
	viewMatrixID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("V");
	modelViewMatrixID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("V");


	//The handler for the texture sampler
	textureID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("textureSampler");

	sgct::ShaderManager::Instance()->unBindShader();
}

void Model::setModelMatrix(glm::mat4 _modelMatrix){
	modelMatrix = _modelMatrix;
	//MVPMatrixID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("MVP");
}

bool Model::hasMesh() const{
    return (mesh != NULL);
}

//Fulkod!!!!
static float rotater = 0;

void Model::drawModel(glm::mat4 P, glm::mat4 V, glm::mat4 M){

	//Use the shader	
	assert(sgct::ShaderManager::Instance()->bindShader(shaderName));

	//En modells position i världen beror på vart dess "parent" befann sig.
	//Tänk på hur stegu snackaded om scengrafer. Model-matrisen talar om
	//hur den här modellen befinner sig i för hållande till sin parent.
	//För att få denna modells position i världen multiplicerar vi med vår
	//parents MVP matris med vår egen model-matrix. På så sätt vet vi hur vi ska
	//rita ut oss. Resultatet, "thisMVP", skickar vi vidare till våra children
	//för att de ska veta dess position i världen.

	glm::mat4 thisMVP = P * V * M * modelMatrix;
	glm::mat4 thisM = M * modelMatrix;
	glm::mat4 MV = V * thisM;

	glUniformMatrix4fv(MVPMatrixID, 1, GL_FALSE, &thisMVP[0][0]);
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &thisM[0][0]);
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &V[0][0]);
	glUniformMatrix4fv(modelViewMatrixID, 1, GL_FALSE, &MV[0][0]);


	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set our "textureSampler" sampler to user Texture Unit 0
	glUniform1i(textureID, 0);


	//Fulkod för att testa att ljuskällan kan flytta på sig
	//(rotater incremantas för övrigt mer då man ritar ut fler saker
	//då den är static vilket gör det ännu fulare HEHAHÖ!)
	rotater = rotater + 0.003;
	if (rotater > 2*3.14)
		rotater = 0;
	Scene::lightSources[0]->position.x = 7 * glm::cos(rotater);
	Scene::lightSources[0]->position.z = 7 * glm::sin(-rotater);


	//Lightsource 1
	glUniform3f(
		Scene::lightSources[0]->lightPositionID,
		Scene::lightSources[0]->position.x,
		Scene::lightSources[0]->position.y,
		Scene::lightSources[0]->position.z);


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
		children[i].drawModel(P, V, thisM);
	}
}
