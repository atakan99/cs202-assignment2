
#include "DecisionTree.h"
#include<iostream>
#include<fstream>
#include <stdio.h>

int main() {
	
	DecisionTree* a = new DecisionTree();
	a->train("train_data.txt", 498, 21);

	double ab = (a->test("test_data.txt", 473));

	cout << "accuracy: " <<  ab <<endl;

	a->print();

	return 0;
}