#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <vector>
#include <string>
#include <map>

using namespace std;

class Evaluator {
	map<string, double>* _symbolTable;

public:
	Evaluator(map<string, double>* symbolTable) {
		_symbolTable = symbolTable;
	}

	double evaluate(vector<string>& arguments, int& index) {
		throw "IS NOT IMPLEMENTED!";
	}
};

#endif //	!EVALUATOR_H