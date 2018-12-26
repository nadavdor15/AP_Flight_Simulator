#include "DefineVarCommand.h"
#include "Expression.h"
#include "StringHelper.h"
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

DefineVarCommand::DefineVarCommand(map<string, double>* symbolTable, map<string, Expression*>* savedNames) {
	_symbolTable = symbolTable;
	_savedNames = savedNames;
	_argumentsAmount = 1;
}

int DefineVarCommand::doCommand(vector<string>& arguments, unsigned int index) {
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

void DefineVarCommand::checkValidity(string varName) {
	if (isdigit(varName[0]))
		throw "The name " + varName + " contains a digit for first char";
	for (unsigned int i = 0; i < varName.length(); i++)
		if (!isalpha(varName[i]) && !isdigit(varName[i]) && varName[i] != '_')
			throw "The name " + varName + " contains a char that is not a-z OR A-Z OR 1-9 OR _";
}