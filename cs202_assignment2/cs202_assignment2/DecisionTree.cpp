/**
* Author: Kaan Atakan Aray
* ID: 21703187
* Section: 1
* Assignment: 2
// compiled with g++ -std=c++11
*/

#include "DecisionTree.h"
#include <cmath>
#include <iostream>
#include<iomanip>


DecisionTreeNode* DecisionTree::addNode(const int featureIndex, const int classDecision, const DecisionTreeNode* leftPtr, const DecisionTreeNode* rightPtr)
{
	DecisionTreeNode* newNode = new DecisionTreeNode();
	newNode->setFeatureIndex(featureIndex);
	newNode->setClassDecision(classDecision);
	newNode->setLeftChildPtr(NULL);
	newNode->setRightChildPtr(NULL);
	return newNode;
}

DecisionTree::DecisionTree()
{
	rootPtr = NULL;
	trainningComp = false;
}

DecisionTree::~DecisionTree()
{
	destroyTree(rootPtr);
}

void DecisionTree::buildTree(DecisionTreeNode* rootPtr, const bool** data, const int* labels, const int numSamples, const int numFeatures, bool* usedSamples, bool* usedFeatures) {

	int label;
	// divide and decide the featureIndex
	int featureId = -1;
	int biggest = 0;
	int classId = -1;
	double* infoGains = new double[numFeatures];

	for (int i = 0; i < numFeatures; i++) {
		infoGains[i] = 0;
		featureId = i;
		if (usedFeatures[i]) {
			continue;
		}
		infoGains[i] = calculateInformationGain(data, labels, numSamples, numFeatures, usedSamples, featureId);
	}

	for (int i = 0; i < numFeatures; i++) {

		if (infoGains[biggest] < infoGains[i]) {
			//cout << infoGains[i] << " " << i << endl;
			biggest = i;
			//cout << biggest << endl;
		}
		featureId = biggest;
	}

	usedFeatures[featureId] = true;

	int* classCountsParent;
	int* classCountsLeft;
	int* classCountsRight;

	bool* usedSamplesLeft = new bool[numSamples];
	bool* usedSamplesRight = new bool[numSamples];

	for (int i = 0; i < numSamples; i++) {
		usedSamplesLeft[i] = usedSamples[i];
		usedSamplesRight[i] = usedSamples[i];
	}
	//int* dataDistribution = new int[numSamples]; // 1 means left, 2 means right

	partition(data, labels, numSamples, numFeatures, usedSamples, featureId, classCountsParent, classCountsLeft, classCountsRight, usedSamplesLeft, usedSamplesRight);


	rootPtr->setFeatureIndex(featureId);

	delete[]classCountsLeft;
	delete[]classCountsRight;
	delete[] infoGains;
	
	if (isPure(classCountsParent, classId)) {
		delete[]usedSamplesLeft;
		delete[]usedSamplesRight;
		delete[]classCountsParent;

		rootPtr->setClassDecision(classId);
		return;
	}

	delete[]classCountsParent;
	rootPtr->setLeftChildPtr(addNode(featureId, classId));
	rootPtr->setRightChildPtr(addNode(featureId, classId));
	
	buildTree(rootPtr->getLeftChildPtr(), data, labels, numSamples, numFeatures, usedSamplesRight, usedFeatures);
	
	buildTree(rootPtr->getRightChildPtr(), data, labels, numSamples, numFeatures, usedSamplesLeft, usedFeatures);

	delete[]usedSamplesLeft;
	delete[]usedSamplesRight;
	
}

bool DecisionTree::isPure(const int* classCounts, int& classId)
{
	int notZeroCount = 0;

	for (int i = 0; i < classCount; i++) {
		if (classCounts[i] > 0) {
			classId = i + 1;
			notZeroCount++;
		}
	}

	if (notZeroCount == 1) {
		return true;
	}
	else {
		return false;
	}
}

void DecisionTree::train(const bool** data, const int* labels, const int numSamples, const int numFeatures)
{

	rootPtr = new DecisionTreeNode();
	DecisionTreeNode * temp = rootPtr;
	// array of used features

	bool* usedFeatures = new bool[numFeatures];

	bool* usedSamples = new bool[numSamples];

	//build tree
	buildTree(temp, data, labels, numSamples, numFeatures, usedSamples, usedFeatures);
	trainningComp = true;

	delete[] usedFeatures;
	delete[] usedSamples;

}


// 498 numSamples, 21 numFeatures
void DecisionTree::train(const string fileName, const int numSamples, const int numFeatures)
{
	// parse the text file that contains the trainning data and call the second train function

	bool** data =  new bool* [numSamples];

	for (int i = 0; i < numSamples; i++) {
		data[i] = new bool[numFeatures];
	}
	
	int* labels = new int[numSamples];


	fstream file(fileName);
	string line;
	int row = 0;
	int column = 0;
	int index = 0;

	
	if (file.is_open()) {

		while (!file.eof() && row < numSamples) {
			getline(file, line);
			//cout << line << endl;
			for (int i = 0; i < line.size(); i++) {
				
				if (line[i] != ' ') {
					if (column == numFeatures) {
						labels[row] = line[i] - '0';
					}
					else {
						data[row][column] = line[i] - '0';
					}
					column++;
				}
			}
			
			column = 0;
			row++;
		}
	}

	featureCount = numFeatures;
	//train
	train((const bool**)data, labels, numSamples, numFeatures);

	// deallocate the arrays
	for (int i = 0; i < numSamples; i++) {
		delete[] data[i];
	}
	delete[] data;
	delete[] labels;

	
}

int DecisionTree::predict(const bool* data)
{
	DecisionTreeNode* tempPtr = rootPtr;
	bool predicted = false;

	while (!predicted) {
		
		if (tempPtr->isLeaf()) {
			
			predicted = true;
			
			return tempPtr->getClassDecision();
		}
		else {
			
			if (data[tempPtr->getFeatureIndex()] == 0) {
				
				tempPtr = tempPtr->getLeftChildPtr();
			}
			else {
				
				tempPtr = tempPtr->getRightChildPtr();
			}
		}
	}
	
}

double DecisionTree::test(const bool** data, const int* labels, const int numSamples)
{
	int numberOfTruePredictions = 0;
	for (int i = 0; i < numSamples; i++) {

		if (predict(data[i]) == labels[i]) {
			
			numberOfTruePredictions = numberOfTruePredictions + 1;
		}
	}
	
	double sampleNumber = numSamples;

	
	
	return (double)((double)numberOfTruePredictions / sampleNumber);
}

// numsamples 473
double DecisionTree::test(const string fileName, const int numSamples)
{
	if (trainningComp) {
		const int numFeatures = featureCount;

		bool** data = new bool* [numSamples];

		for (int i = 0; i < numSamples; i++) {
			data[i] = new bool[numFeatures];
		}

		int* labels = new int[numSamples];

		fstream file(fileName);
		string line;
		int row = 0;
		int column = 0;
		int index = 0;


		if (file.is_open()) {

			while (!file.eof() && row < numSamples) {
				getline(file, line);
				//cout << line << endl;
				for (int i = 0; i < line.size(); i++) {

					if (line[i] != ' ') {
						if (column == numFeatures) {
							labels[row] = (int)(line[i] - '0');
						}
						else {
							data[row][column] = line[i] - '0';
						}
						column++;
					}
				}
				column = 0;
				row++;
			}
		}

		
		//return precision
		double result =  test((const bool**)data, labels, numSamples);

		for (int i = 0; i < numSamples; i++) {
			delete[] data[i];
		}
		delete[] data;
		delete[] labels;
		return result;
		
	}
	else {
		cout << "Test function cannot be called before train function." << endl;
		return 0.0;
	}
}

void DecisionTree::print()
{
	if (trainningComp) {
		DecisionTreeNode* tempPtr = rootPtr;
		int levelIndex = 0;

		printPreorder(tempPtr, levelIndex);
	}
	else {
		cout << "Print function cannot be called before train function." << endl;
	}
}


// make calculate entropy and info gain suitable for more than 3 label (or all number of labels)
double DecisionTree::calculateEntropy(const int* classCounts, const int numClasses)
{
	double entropy = 0.0;
	double sumOfCounts = 0.0;

	//for finding the sum
	for (int i = 0; i < numClasses; i++) {
		sumOfCounts += classCounts[i];
	}
	// calculate entropy
	for (int i = 0; i < numClasses; i++) {
		double a = (double)(classCounts[i]) / (double)(sumOfCounts);
		if (a > 0) {
			entropy -= (a * log2(a));
		}
	}
	//cout << entropy << endl;
	return entropy;
}



double DecisionTree::calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId)
{
	// create class counts array

	int* classCountsParent;
	int* classCountsLeft;
	int* classCountsRight;

	bool* usedLeft = NULL;
	bool* usedRight = NULL;

	partition(data, labels, numSamples, numFeatures, usedSamples, featureId, classCountsParent, classCountsLeft, classCountsRight, usedLeft, usedRight);

	double informationGain = 0.0;
	double entropyParent = 0.0;
	double entropySplit = 0.0;
	double probLeft = 0.0;
	double probRight = 0.0;


	entropyParent = calculateEntropy(classCountsParent, classCount);

	double  probLeft1 = 0.0;
	double probLeft2 = 0.0;

	for (int i = 0; i < classCount; i++) {
		probLeft1 += (double)(classCountsLeft[i]);
		probLeft2 += (double)(classCountsParent[i]);
	}

	probLeft = probLeft1 / probLeft2;

	//probRight = (double)(classCountsRight[0] + classCountsRight[1] + classCountsRight[2]) / (double)(classCountsParent[0] + classCountsParent[1] + classCountsParent[2]);
	probRight = 1 - probLeft;

	entropySplit = (probLeft * calculateEntropy(classCountsLeft, classCount)) + (probRight * calculateEntropy(classCountsRight, classCount));

	informationGain = entropyParent - entropySplit;

	//cout << informationGain << endl;

	delete[] classCountsParent;
	delete[] classCountsLeft;
	delete[] classCountsRight;
	delete[] usedLeft;
	delete[] usedRight;

	return informationGain;

}

int* DecisionTree::findClassLabels(const int* labels, const int numSamples, int& labelCount) {

	int* labelSorted = new int[numSamples];

	for (int i = 0; i < numSamples; i++) {
		labelSorted[i] = labels[i];
	}

	//insertion sort
	for (int unsorted = 1; unsorted < numSamples; ++unsorted) {

		int nextItem = labelSorted[unsorted];
		int loc = unsorted;

		for (; (loc > 0) && (labelSorted[loc - 1] > nextItem); --loc)
			labelSorted[loc] = labelSorted[loc - 1];

		labelSorted[loc] = nextItem;

	}

	for (int i = 1; i < numSamples; i++) {
		if (labelSorted[i - 1] != labelSorted[i]) {
			labelCount++;
		}
	}

	classCount = labelCount;

	//cout << "------" << classCount <<endl;
	const int labelCountConst = labelCount;
	int* lc = new int[labelCount];
	int lcindex = 0;

	for (int i = 1; i < numSamples; i++) {
		if (labelSorted[i - 1] != labelSorted[i]) {
			lc[lcindex] = labelSorted[i - 1];
			lc[lcindex + 1] = labelSorted[i];
			lcindex++;
		}

	}

	//returns an aray of label types
	delete[] labelSorted;
	return lc;
}

void DecisionTree::partition(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId, int*& classCP, int*& classCL, int*& classCR, bool*& usedSamplesLeft, bool*& usedSamplesRight) {

	int labelCountTemp = 1;

	int* labelTypes = findClassLabels(labels, numSamples, labelCountTemp);

	const int labelCount = labelCountTemp;

	int* classCountsParent = new int[labelCount];
	int* classCountsLeft = new int[labelCount];
	int* classCountsRight = new int[labelCount];

	double informationGain = 0.0;
	double entropyParent = 0.0;
	double entropySplit = 0.0;
	double probLeft = 0.0;
	double probRight = 0.0;

	for (int i = 0; i < labelCount; i++) {
		classCountsLeft[i] = 0.0;
		classCountsRight[i] = 0.0;
		classCountsParent[i] = 0.0;
	}

	for (int i = 0; i < numSamples; i++) {
		int labelTypeIndex = 0;
		if (!usedSamples[i]) {
			while (labels[i] != labelTypes[labelTypeIndex]) {
				labelTypeIndex++;
			}
			classCountsParent[labelTypeIndex]++;
		}
	}

	for (int i = 0; i < numSamples; i++) {

		int labelTypeIndex = 0;

		if (!usedSamples[i]) {
			if (data[i][featureId] == 0) { // data[i][featureId] == false (left part)
				if (usedSamplesLeft != NULL) {
					usedSamplesLeft[i] = true;
				}
				while (labels[i] != labelTypes[labelTypeIndex]) {
					labelTypeIndex++;
				}
				classCountsLeft[labelTypeIndex]++;
			}
			labelTypeIndex = 0;
			if (data[i][featureId] == 1) { //data[i][featureId] == true (right part)
				if (usedSamplesRight != NULL) {
					usedSamplesRight[i] = true;
				}
				
				while (labels[i] != labelTypes[labelTypeIndex]) {
					labelTypeIndex++;
				}
				classCountsRight[labelTypeIndex]++;

			}
		}


	}

	classCP = classCountsParent;
	classCL = classCountsLeft;
	classCR = classCountsRight;

	
	delete [] labelTypes;
}

void DecisionTree::printPreorder(DecisionTreeNode* node, int level)
{
	
	if (node->isLeaf()) {
		for (int i = 0; i < level; i++) {
			cout << "\t";
		}

		cout <<"class="<<node->getClassDecision()<<endl;
		return;
	}

	for (int i = 0; i < level; i++) {
		cout << "\t";
	}
	cout << "feature=" <<node->getFeatureIndex() << endl;
	
	printPreorder(node->getLeftChildPtr(), ++level);

	printPreorder(node->getRightChildPtr(), level);

}

int DecisionTree::getHeight(DecisionTreeNode* subTreePtr)
{
	if (subTreePtr == NULL)
		return 0;
	else {
		if (getHeight(subTreePtr->getLeftChildPtr()) < getHeight(subTreePtr->getRightChildPtr()))
			return 1 + getHeight(subTreePtr->getRightChildPtr());
		else
			return 1 + getHeight(subTreePtr->getLeftChildPtr());
	}
		
}

void DecisionTree::destroyTree(DecisionTreeNode* subTreePtr)
{
	if (subTreePtr != nullptr)
	{
		destroyTree(subTreePtr->getLeftChildPtr());
		destroyTree(subTreePtr->getRightChildPtr());
		delete subTreePtr;
	}  // end if 

}
