#include "Expression.h"
#include "Command.h"
#include "StringHelper.h"
#include <iostream>
#include <math.h>

using namespace std;

class DefineVarCommand : public Command {
	map<string, Expression*>* _savedNames;

public:
	DefineVarCommand(map<string, double>* symbolTable, map<string, Expression*>* savedNames) {
		_symbolTable = symbolTable;
		_savedNames = savedNames;
		_argumentsAmount = 1;
	}

	virtual int doCommand(vector<string>& arguments, unsigned int index) {
		if ((arguments.size() - 1) < _argumentsAmount)
			throw "Amount of arguments is lower than " + to_string(_argumentsAmount);
		if (_symbolTable->find(arguments[++index]) != _symbolTable->end())
			throw "The variable " + arguments[index] + " cannot be redefined";
		if (_savedNames->find(arguments[index]) != _savedNames->end())
			throw "The name " + arguments[index] + " is a saved word";
		string argument = StringHelper::getArgument(arguments);
		StringHelper::addSpaces(argument);
		arguments = StringHelper::split(argument, " ");
		checkValidity(arguments[index]);
		_symbolTable->operator[](arguments[index]) = NAN;
		return ++index;
	}

private:
	void checkValidity(string varName) {
		for (unsigned int i = 0; i < varName.length(); i++)
			if ((varName[i] < 'a' || varName[i] > 'z') && varName[i] != '_' &&
				(varName[i] < 'A' || varName[i] > 'Z') && ('0' > varName[i] || varName[i] > '9'))
				throw "The name " + varName + " contains a char that is not a-z OR A-Z OR 1-9 OR _";
		if ('0' <= varName[0] && varName[0] <= '9')
			throw "The name " + varName + " contains a digit for first char";
	}
};