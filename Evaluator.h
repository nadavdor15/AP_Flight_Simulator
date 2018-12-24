#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <vector>
#include <string>
#include <iostream>
#include "Number.h"
#include <map>

using namespace std;

class Evaluator {
	static map<string, int> _precedenceMap;
	static double calculatePostfix(vector<string> arguments);
	static vector<string> assignVars(vector<string>, unsigned int*, map<string, double>*);
	static unsigned int lastIndex(vector<string> arguments, unsigned int* index, map<string, double>* symbolTable);
	static vector<string> toPostfix(vector<string> arguments, unsigned int* index, map<string, double>* symbolTable);
	static Number calculateNumber(string operant, Number leftNumber, Number rightNumber);
public:
	static double evaluate(vector<string> arguments, unsigned int* index, map<string, double>* symbolTable);
};

#endif //	!EVALUATOR_H