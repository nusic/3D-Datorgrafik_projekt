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
	for (int i = 0; i < children.size(); ++i){
		if (children[i] != NULL){
			children[i]->update(dt);
		}
	}
}

void Node::draw(glm::mat4 &P, glm::mat4 &V, glm::mat4 &parentModelMatrix){
	for (int i = 0; i < children.size(); ++i){
		if (children[i] != NULL){
			children[i]->draw(P, V, parentModelMatrix);
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
		for(int i = 0; i<children.size(); ++i){
			if(children[i] == childNode){
				children.erase(children.begin() + i);
				break;
			}
		}
	}	
}

Node* Node::getChild(int index) const{
	return children[index];
}

Node* Node::getChildByName(const std::string &searchName) const{
	for(int i = 0; i<children.size(); ++i){
		if(searchName == children[i]->name){
			return children[i];
		}
	}
	return NULL;
}

int Node::countChildNodes(const bool &recursiveCount) const{
	if(!recursiveCount){
		return children.size();
	}
	else{
		int count = children.size();
		for(int i = 0; i<children.size(); ++i){
			count += children[i]->countChildNodes(recursiveCount);
		}
		return count;
	}
}