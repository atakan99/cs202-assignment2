/**
* Author: Kaan Atakan Aray
* ID: 21703187
* Section: 1
* Assignment: 2
*/

#include "DecisionTreeNode.h"

DecisionTreeNode::DecisionTreeNode()
{
	featureIndex = -1; // invalid value
	classDecision = 0; // invalid value
	leftChildPtr = NULL;
	rightChildPtr = NULL;
}


void DecisionTreeNode::setFeatureIndex(int featureInd)
{
	this->featureIndex = featureInd;
}

void DecisionTreeNode::setClassDecision(int classD)
{
	this->classDecision = classD;
}


int DecisionTreeNode::getFeatureIndex()
{
	return featureIndex;
}

int DecisionTreeNode::getClassDecision()
{
	return classDecision;
}



bool DecisionTreeNode::isLeaf() const
{
	if (this->getLeftChildPtr() == NULL && this->getRightChildPtr() == NULL) {
		
		return true;
	}
	else {
		
		return false;
	}
}

DecisionTreeNode* DecisionTreeNode::getLeftChildPtr() const
{
	return leftChildPtr;
}

DecisionTreeNode* DecisionTreeNode::getRightChildPtr() const
{
	return rightChildPtr;
}

void DecisionTreeNode::setLeftChildPtr(DecisionTreeNode* leftPtr)
{
	leftChildPtr = leftPtr;
}

void DecisionTreeNode::setRightChildPtr(DecisionTreeNode* rightPtr)
{
	rightChildPtr = rightPtr;
}
