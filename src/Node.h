#ifndef NODE_H
#define NODE_H 

#include <vector>
#include <string>
#include <cassert>
#include "sgct.h"

//This class is based on the tutorial from
//http://scriptionary.com/2009/02/17/simple-scene-graph-in-c/

class Node{

public:
	Node(Node * _parent = NULL, std::string _name = "");
	virtual ~Node();

	virtual void draw(glm::mat4 &P, glm::mat4 &V, glm::mat4 &parentModelMatrix);
	void update(float dt);

	Node* getParentNode() const;
	void setParentNode(Node * parent);

	void addChildNode(Node* child);
	void removeChildNode(Node* child);

	std::string getNodeName() const;
	int countChildNodes(const bool &recursiveCount) const;

	Node* getChild(int index) const;
	Node* getChildByName(const std::string &searchName) const;


private:

	Node * parent;
	std::string name;
	std::vector<Node*> children;
	
};

#endif