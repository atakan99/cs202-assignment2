
/**
* Author: Kaan Atakan Aray
* ID: 21703187
* Section: 1
* Assignment: 2
*/

#include <cmath>
#include<string>
using namespace std;


//class calculateFunctions {
//public:
//	double calculateEntropy(const int* classCounts, const int numClasses)
//	{
//		double entropy = 0;
//		double sumOfCounts = 0;
//
//		//for finding the sum
//		for (int i = 0; i < numClasses; i++) {
//			sumOfCounts += classCounts[i];
//		}
//
//		// calculate entropy
//		for (int i = 0; i < numClasses; i++) {
//
//			entropy += classCounts[i] / sumOfCounts * log2(classCounts[i] / sumOfCounts);
//		}
//
//		entropy = 0 - entropy;
//		return entropy;
//	}
//
//	double calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId)
//	{
//		// create class counts array
//
//		int* classCountsParent = new int[3];
//		int* classCountsLeft = new int[3];
//		int* classCountsRight = new int[3];
//
//		double informationGain = 0.0;
//		double entropyParent = 0.0;
//		double entropySplit = 0.0;
//		double probLeft = 0.0;
//		double probRight = 0.0;
//
//		for (int i = 0; i < 3; i++) {
//			classCountsLeft[i] = 0;
//			classCountsRight[i] = 0;
//			classCountsParent[i] = 0;
//		}
//
//		for (int i = 0; i < numSamples; i++) {
//
//			if (!usedSamples[i]) {
//				if (labels[i] == 1) {
//					classCountsParent[0]++;
//				}
//				if (labels[i] == 2) {
//					classCountsParent[1]++;
//				}
//				if (labels[i] == 3) {
//					classCountsParent[2]++;
//				}
//			}
//		}
//			for (int i = 0; i < numSamples; i++) {
//				if (!usedSamples[i]) {
//					if (!data[i][featureId]) { // data[i][featureId] == false
//
//						if (labels[i] == 1) {
//							classCountsLeft[0]++;
//						}
//						if (labels[i] == 2) {
//							classCountsLeft[1]++;
//						}
//						if (labels[i] == 3) {
//							classCountsLeft[2]++;
//						}
//					}
//				}
//
//				if (data[i][featureId]) { //data[i][featureId] == true
//					if (!usedSamples[i]) {
//						if (labels[i] == 1) {
//							classCountsRight[0]++;
//						}
//						if (labels[i] == 2) {
//							classCountsRight[1]++;
//						}
//						if (labels[i] == 3) {
//							classCountsRight[2]++;
//						}
//					}
//				}
//			}
//
//			entropyParent = calculateEntropy(classCountsParent, 3);
//
//			probLeft = (classCountsLeft[0] + classCountsLeft[1] + classCountsLeft[2]) / (classCountsParent[0] + classCountsParent[1] + classCountsParent[2]);
//
//			probRight = (classCountsRight[0] + classCountsRight[1] + classCountsRight[2]) / (classCountsParent[0] + classCountsParent[1] + classCountsParent[2]);
//
//			entropySplit = (probLeft * calculateEntropy(classCountsLeft, 3)) + (probRight * calculateEntropy(classCountsRight, 3));
//
//			informationGain = entropyParent - entropySplit;
//
//			return informationGain;
//		
//	}
//
//};