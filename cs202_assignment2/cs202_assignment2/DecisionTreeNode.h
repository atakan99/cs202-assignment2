/**
* Author: Kaan Atakan Aray
* ID: 21703187
* Section: 1
* Assignment: 2
*/


#ifndef _DECISION_TREE_NODE 
#define _DECISION_TREE_NODE 

#include <string>
//template<class ItemType>
class DecisionTreeNode
{
private:
    
    int featureIndex;// 0 - numFeatures -1 
    int classDecision; // 1, 2 or 3

    DecisionTreeNode* leftChildPtr;  // Pointer to left child 
    DecisionTreeNode* rightChildPtr; // Pointer to right child 

   
public:
    DecisionTreeNode();
    

    void setFeatureIndex(int featureIndex);
    void setClassDecision(int classDecision);

    int getFeatureIndex();
    int getClassDecision();

   // void setIsLeafNode();
    bool isLeaf() const;
    
    DecisionTreeNode* getLeftChildPtr() const;
    DecisionTreeNode* getRightChildPtr() const;
    
    void setLeftChildPtr(DecisionTreeNode* leftPtr);
    void setRightChildPtr(DecisionTreeNode* rightPtr);
}; 

#endif 



