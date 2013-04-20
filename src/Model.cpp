#include "Model.h"

Model::Model(ModelMesh* _mesh, glm::mat4 M): 
modelMatrix(M), mesh(_mesh) {
	std::cout << "created Model" << std::endl;
}

void Model::setShader(std::string s){
	shaderName = s;
}


void Model::drawModel(glm::mat4 MVP) const{
	//Use the shader
	//sgct::ShaderManager::Instance()->bindShader(shaderName);

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