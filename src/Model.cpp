#include "Model.h"

Model::Model(ModelMesh* _mesh, glm::mat4 M, std::string _shaderName){
	mesh = _mesh;
	setModelMatrix(M);
	setShader(_shaderName);

	std::cout << "created Model" << std::endl;
}

void Model::setShader(std::string _shaderName){

}
	
void Model::setModelMatrix(glm::mat4 _modelMatrix){

}



void Model::drawModel(glm::mat4 MVP) const{
	//Use the shader
	//sgct::ShaderManager::Instance()->bindShader(shaderName);

	//----------ERIK JOBBAR HÄR OCH NEDÅT ----------


	//glm::mat thisMVP = MVP * modelMatrix;


	//----------ERIK JOBBAR HÄR OCH UPPÅT ----------

	
	//Attribute the vertices buffer
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexbufferID);
	glVertexAttribPointer(
		0, // The attribute we want to configure (vertexPosShaderID)
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

	//sgct::ShaderManager::Instance()->unBindShader();
}