#include "Model.h"

Model::Model(ModelMesh* _mesh, glm::mat4 M, std::string _shaderName){
	mesh = _mesh;
	setShader(_shaderName);
	setModelMatrix(M);

	std::cout << "created Model" << std::endl;
}

void Model::setShader(std::string _shaderName){

	shaderName = _shaderName;

	sgct::ShaderManager::Instance()->bindShader(shaderName);

	//The handle for the vertex data
	vertexShaderID = sgct::ShaderManager::Instance()->getShader(shaderName).getAttribLocation("vertexPosition");
	normalShaderID = sgct::ShaderManager::Instance()->getShader(shaderName).getAttribLocation("vertexNormal");
	UVShaderID = sgct::ShaderManager::Instance()->getShader(shaderName).getAttribLocation("UV");
	//The handle for the MVP-matrix
	matrixShaderID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("MVP");

	std::cout << "mesh->vertices.size() = " << mesh->vertices.size() << std::endl;

	//Generate a buffer for the vertex list
	glGenBuffers(1, &(mesh->vertexbufferID));
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexbufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mesh->vertices.size(), &(mesh->vertices[0]), GL_STATIC_DRAW);

	//Generate a buffer for the vertex list
	glGenBuffers(1, &(mesh->normalbufferID));
	glBindBuffer(GL_ARRAY_BUFFER, mesh->normalbufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mesh->normals.size(), &(mesh->normals[0]), GL_STATIC_DRAW);

	//Generate a buffer for the vertex list
	glGenBuffers(1, &(mesh->uvbufferID));
	glBindBuffer(GL_ARRAY_BUFFER, mesh->normalbufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mesh->uvs.size(), &(mesh->uvs[0]), GL_STATIC_DRAW);

	sgct::ShaderManager::Instance()->unBindShader();
}
	
void Model::setModelMatrix(glm::mat4 _modelMatrix){
	modelMatrix = _modelMatrix;
	modelMatrixID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("MVP");
}



void Model::drawModel(glm::mat4 MVP) const{
	//Use the shader
	//sgct::ShaderManager::Instance()->bindShader(shaderName);

	//----------ERIK JOBBAR HÄR OCH NEDÅT ----------

	//En modells position i världen beror på vart dess "parent" befann sig.
	//Tänk på hur stegu snackaded om scengrafer. Model-matrisen talar om
	//hur den här modellen befinner sig i för hållande till sin parent. 
	//För att få denna modells position i världen multiplicerar vi med vår 
	//parents MVP matris med vår egen model-matrix. På så sätt vet vi hur vi ska 
	//rita ut oss. Resultatet, "thisMVP", skickar vi vidare till våra children
	//för att de ska veta dess position i världen.
	glm::mat4 thisMVP = MVP * modelMatrix;
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &thisMVP[0][0]);
	

	//----------ERIK JOBBAR HÄR OCH UPPÅT ----------

	sgct::ShaderManager::Instance()->bindShader(shaderName);

	//Attribute the vertices buffer
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexbufferID);
	glVertexAttribPointer(
		vertexShaderID, // The attribute we want to configure (vertexPosShaderID)
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangle!
	// 3 indices starting at 0 -> 1 triangle
	glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.size());

	glDisableVertexAttribArray(0);

	sgct::ShaderManager::Instance()->unBindShader();

}