#include "Node.h"

Node::Node(Node * _parent, std::string _name){
	name = _name;
	parent = NULL;

	if(_parent != NULL){
		_parent->addChildNode(this);
	}
}

Node::~Node(){
	parent = NULL;
	children.clear();
}

void Node::update(float dt){
	for (unsigned int i = 0; i < children.size(); ++i){
		if (children[i] != NULL){
			children[i]->update(dt);
		}
	}
}

int Node::getNumberOfVertices() const{
	int sum = 0;
	for (unsigned int i = 0; i < children.size(); ++i){
		if (children[i] != NULL){
			sum += children[i]->getNumberOfVertices();
		}
	}
	return sum;
}

void Node::renderToScreen(glm::mat4 &P, glm::mat4 &V, glm::mat4 &M){
	for (unsigned int i = 0; i < children.size(); ++i){
		if (children[i] != NULL){
			children[i]->renderToScreen(P, V, M);
		}
	}
}

void Node::renderToDepthBuffer(glm::mat4 &VP, glm::mat4 &M){
	for (unsigned int i = 0; i < children.size(); ++i){
		if (children[i] != NULL){
			children[i]->renderToDepthBuffer(VP, M);
		}
	}
}

Node* Node::getParentNode() const{
	return parent;
}

void Node::setParentNode(Node* newParent){
	if(parent != NULL){
		parent->removeChildNode(this);
	}
	parent = newParent;
}

void Node::addChildNode(Node* childNode){
	assert(childNode != NULL);
	children.push_back(childNode);
	childNode->setParentNode(this);

}

void Node::removeChildNode(Node* childNode){
	if(childNode != NULL && !children.empty()){
		for(unsigned int i = 0; i<children.size(); ++i){
			if(children[i] == childNode){
				children.erase(children.begin() + i);
				break;
			}
		}
	}
}

void Node::removeFromParent(){
	parent->removeChildNode(this);
}

void Node::insertAfter(Node* n){
	Node * temp;
	for(int i = 0; i < n->children.size(); ++i){
		temp = n->children[i];
		n->removeChildNode(temp);
		addChildNode(temp);
	}
	n->addChildNode(this);
}

Node* Node::getChild(int index) const{
	return children[index];
}

Node* Node::getChildByName(const std::string &searchName) const{
	for(unsigned int i = 0; i<children.size(); ++i){
		if(searchName == children[i]->name){
			return children[i];
		}
	}
	return NULL;
}

std::vector<Node*>& Node::getNodesByName(const std::string &searchName) const{
	std::vector<Node*>* v = new std::vector<Node*>;
	addNodesToVectorByName(v, searchName);
	return *v;
}

void Node::addNodesToVectorByName(std::vector<Node*> * v, const std::string &searchName) const{
	for (int i = 0; i < children.size(); ++i){
		if(children[i]->name == searchName)
			v->push_back(children[i]);
		children[i]->addNodesToVectorByName(v, searchName);
	}
}

int Node::countChildNodes(const bool &recursiveCount) const{
	if(!recursiveCount){
		return children.size();
	}
	else{
		int count = children.size();
		for(unsigned int i = 0; i<children.size(); ++i){
			count += children[i]->countChildNodes(recursiveCount);
		}
		return count;
	}
}
