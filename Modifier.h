#ifndef MODIFIER_H
#define MODIFIER_H

#include "CommandExpression.h"

using namespace std;

class Modifier {
protected:
	map<string, vector<string>>* _bindedVarTable;
	map<string, double>* _symbolTable;

public:
	Modifier(map<string, vector<string>>* bindedVarTable,
			 map<string, double>* symbolTable);
	void setVariableValue(string var, double value);
};

#endif