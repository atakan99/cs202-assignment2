
/**
* Author: Kaan Atakan Aray
* ID: 21703187
* Section: 1
* Assignment: 2
*/

#ifndef _DECISION_TREE 
#define _DECISION_TREE 

#include <string>
#include <fstream>
#include <ostream>
#include "DecisionTreeNode.h" 
using namespace std;



class DecisionTree
{
private:
  DecisionTreeNode * rootPtr;
  bool trainningComp;
   int classCount;
   int featureCount;

  
 
  DecisionTreeNode* addNode(const int featureIndex = -1 ,const int classDecision = 0, const DecisionTreeNode* leftPtr = NULL, const DecisionTreeNode* rightPtr = NULL);  // Adds a node
 
void buildTree(DecisionTreeNode* rootPtr, const bool** data, const int* labels, const int numSamples, const int numFeatures,  bool* usedSamples, bool* usedFeatures);

  bool isPure( const int * classCounts, int& classId );

  int* findClassLabels(const int* labels, const int numSamples, int& labelCount);
  void partition(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId, int*& classCP, int*& classCL, int*& classCR, bool*& usedSamplesLeft , bool*& usedSamplesRight );
 
  void printPreorder(DecisionTreeNode* node, int levelIndex);

  int getHeight(DecisionTreeNode* subTreePtr);

  void destroyTree(DecisionTreeNode* subTreePtr);

public:
    
    DecisionTree();
   
    ~DecisionTree();
    
    void train(const bool** data, const int* labels, const int numSamples, const int numFeatures);
    void train(const string fileName, const int numSamples, const int numFeatures);

    int predict(const bool* data);

    double test(const bool** data, const int* labels, const int numSamples);
    double test(const string fileName, const int numSamples);

    void print();

    double calculateEntropy(const int* classCounts, const int numClasses);

    double calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId);
};  

#endif 