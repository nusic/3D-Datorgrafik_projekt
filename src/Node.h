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
	Node(Node * _parent = NULL, const std::string &_name = "");
	virtual ~Node();


	virtual int getNumberOfVertices() const;
	virtual void renderToScreen(const glm::mat4 &P, const glm::mat4 &V, const glm::mat4 &M);
	virtual void renderToDepthBuffer(const glm::mat4 &VP, const glm::mat4 &M);
	virtual const glm::vec4& backtraceToWorldSpace(const glm::vec4& M) const;
	void update(float dt);

	Node* getParentNode() const;
	void setParentNode(Node * parent);

	void addChildNode(Node* child);
	void removeChildNode(Node* child);
	void removeFromParent();
	void insertAfter(Node* node);

	std::string getNodeName() const;
	int countChildNodes(const bool &recursiveCount) const;

	Node* getChild(int index) const;
	Node* getChildByName(const std::string &searchName) const;
	std::vector<Node*>& getNodesByName(const std::string &searchName) const;


private:

	void addNodesToVectorByName(std::vector<Node*> * v, const std::string &searchName) const;

	Node * parent;
	const std::string name;
	std::vector<Node*> children;
	
};

#endif