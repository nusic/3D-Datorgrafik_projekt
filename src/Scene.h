#ifndef SCENE_H
#define SCENE_H

#include "sgct.h"
#include "Model.h"
#include "GameObject.h"



class Scene : public Model{
public:
	Scene(ModelMesh* _mesh = NULL, 
		  glm::mat4 M = glm::mat4(1.0), 
		  std::string _shaderName = "SimpleColor");
	
	~Scene();

	void initScene();
	void drawScene(glm::mat4 ViewPerspectiveMatrix) const;

private:

};

#endif