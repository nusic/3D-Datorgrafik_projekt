#include "ModelMesh.h"
#include <iostream>


ModelMesh::ModelMesh(const std::string &path, float scale){ 
	if(loadOBJ(path.c_str(), scale, scale, scale)){
		generateGLBuffers();
		calcRadiusXZ();
	}
	else printf("ERROR: COULDN'T READ OBJECT\n");
}

ModelMesh::ModelMesh(const std::string &path, float sx, float sy, float sz){ 
	if(loadOBJ(path.c_str(), sx, sy, sz)){
		generateGLBuffers();
		calcRadiusXZ();
	}
	else printf("ERROR: COULDN'T READ OBJECT\n");
}

ModelMesh::~ModelMesh(){
	deleteGLBuffers();
}

float ModelMesh::getRadius() const{
	return vertexRadiusXZ;
}

glm::vec3 ModelMesh::getMaxVertexValues(){
    glm::vec3 maxValues = vertices[0];
    for(int i = 1; i<vertices.size(); ++i){
        if(vertices[i].x > maxValues.x) maxValues.x = vertices[i].x;
        if(vertices[i].y > maxValues.y) maxValues.y = vertices[i].y;
        if(vertices[i].z > maxValues.z) maxValues.z = vertices[i].z;
    }
    return maxValues;
}

glm::vec3 ModelMesh::getMinVertexValues(){
    glm::vec3 minValues = vertices[0];
    for(int i = 1; i<vertices.size(); ++i){
        if(vertices[i].x < minValues.x) minValues.x = vertices[i].x;
        if(vertices[i].y < minValues.y) minValues.y = vertices[i].y;
        if(vertices[i].z < minValues.z) minValues.z = vertices[i].z;
    }
    return minValues;
}

void ModelMesh::calcRadiusXZ(){
	float maxSquaredRadius = 0.0f;
	float temp = 0.0f;

	for (int i = 0; i < vertices.size(); ++i){
		temp = glm::pow(vertices[i].x, 2.0f) + glm::pow(vertices[i].z, 2.0f);
		if(temp > maxSquaredRadius)
			maxSquaredRadius = temp;
	}

	vertexRadiusXZ = glm::pow(maxSquaredRadius, 0.5f);
}


bool ModelMesh::loadOBJ(const char * path, float sx, float sy, float sz){
	printf("Loading OBJ file %s... ", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices; 
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;


	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		return false;
	}

	while( 1 ){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		
		if ( strcmp( lineHeader, "v" ) == 0 ){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}else if ( strcmp( lineHeader, "vt" ) == 0 ){
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			//uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (matches != 9){
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[1]);
			uvIndices    .push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for( unsigned int i=0; i<vertexIndices.size(); i++ ){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		
		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		glm::vec2 uv = temp_uvs[ uvIndex-1 ];
		glm::vec3 normal = temp_normals[ normalIndex-1 ];
		
		// Resize
		vertex.x *= sx;
		vertex.y *= sy;
		vertex.z *= sz;

		// Put the attributes in buffers
		vertices.push_back(vertex);
		uvs     .push_back(uv);
		normals .push_back(normal);
	
	}
	printf("verts: %i\n", (int)vertices.size());
	return true;
}

void ModelMesh::generateGLBuffers(){
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
}

void ModelMesh::deleteGLBuffers(){
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &uvBuffer);
	glDeleteBuffers(1, &normalBuffer);
}
