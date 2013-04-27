#ifndef SCENE_H
#define SCENE_H

#include "sgct.h"
#include "Model.h"
#include "GameObject.h"
#include "LightSource.h"
#include <vector>


class Scene : public Model{
public:
	Scene();

	~Scene();

	void initScene();
	void drawScene(glm::mat4 ViewPerspectiveMatrix);

	void addGenerations(Model& mother, int n);

	static std::vector<LightSource*> lightSources;

private:

};

#endif
