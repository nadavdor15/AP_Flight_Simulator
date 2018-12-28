#ifndef MODIFIER_H
#define MODIFIER_H

#include "CommandExpression.h"
#include "ConnectCommand.h"

using namespace std;

/*
* class that manages all of the variables values in our interpreter.
* */
class Modifier {
protected:
	map<string, vector<string>>* _bindedVarTable;
	map<string, double>* _symbolTable;
	map<string, string>* _varToPath;
	ConnectCommand* _connectCommand;

public:
	Modifier(map<string, vector<string>>* bindedVarTable,
			 map<string, double>* symbolTable,
			 map<string, string>* varToPath,
			 ConnectCommand* connectCommand);
	void setVariableValue(string var, double value);
	void updateSimulator(string varName);
};

#endif
