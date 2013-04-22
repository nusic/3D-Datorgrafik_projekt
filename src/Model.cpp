
#include "Model.h"


Model::Model(ModelMesh* _mesh, glm::mat4 M, std::string _shaderName){
	mesh = _mesh;
	if(!mesh)
		std::cout << "WARNING: MODEL WITH NULL MESH CREATED!!!!!" << std::endl;
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

	sgct::ShaderManager::Instance()->unBindShader();
}
	
void Model::setModelMatrix(glm::mat4 _modelMatrix){
	modelMatrix = _modelMatrix;
	modelMatrixID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("MVP");
}


float angle = 0.0f;

void Model::drawModel(glm::mat4 MVP){
	//Use the shader

	
	assert(sgct::ShaderManager::Instance()->bindShader(shaderName));

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


	//Attribute the vertices buffer
	glEnableVertexAttribArray(vertexShaderID);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexbufferID);
	glVertexAttribPointer(
		vertexShaderID, // The attribute we want to configure (vertexShaderID)
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	//Attribute the normal buffer
	glEnableVertexAttribArray(normalShaderID);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->normalbufferID);
	glVertexAttribPointer(
		normalShaderID, // The attribute we want to configure (normalShaderID)
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangles!
	// 3 indices starting at 0 -> 1 triangle
	glDrawArrays(GL_TRIANGLES, 0, mesh->normals.size());

	glDisableVertexAttribArray(vertexShaderID);
	glDisableVertexAttribArray(normalShaderID);

	sgct::ShaderManager::Instance()->unBindShader();

	for(int i = 0; i<children.size(); ++i){
		children[i].drawModel(thisMVP);
	}
}