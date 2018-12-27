#include "AssignCommand.h"
#include "StringHelper.h"
#include "Evaluator.h"

AssignCommand::AssignCommand(map<string, double>* symbolTable,
							 map<string, string>* pathToVar,
							 map<string, vector<string>>* bindedVarTable,
							 Modifier* modifier) {
	_symbolTable = symbolTable;
	_pathToVar = pathToVar;
	_bindedVarTable = bindedVarTable;
	_modifier = modifier;
	_argumentsAmount = 2;
}

int AssignCommand::doCommand(vector<string>& arguments, unsigned int index) {
	if ((arguments.size() - 1) < _argumentsAmount)
		throw "Arguments amount is lower than " + to_string(_argumentsAmount);
	if (_symbolTable->find(arguments[index - 1]) == _symbolTable->end())
		throw "The variable " + arguments[index - 1] + " is not defined";
	string argument = StringHelper::getArgument(arguments);
	if ((arguments.size() - index - 1) >= 2) {
		if (arguments[index + 1].compare(string("bind")) == 0) {
			string path = arguments[index + 2];
			int path_length = path.length();
			string bindToVar = arguments[index + 2];
			string bindFromVar = arguments[index - 1];
			if (path[0] == '\"' && path[path_length - 1] == '\"') {
				path = path.substr(1, path_length - 2);
				_pathToVar->operator[](path) = bindFromVar;
				_pathToVar->operator[](bindFromVar) = path;
				_bindedVarTable->operator[](bindFromVar).push_back(path);
			} else if (_symbolTable->find(bindToVar) != _symbolTable->end()) {
				_bindedVarTable->operator[](bindFromVar).push_back(bindToVar);
				_bindedVarTable->operator[](bindToVar).push_back(bindFromVar);
				_symbolTable->operator[](bindFromVar) = _symbolTable->operator[](bindToVar);
			} else
				throw "Could not bind the var " + arguments[index - 1];
			return index + 3;
		}
	}
	int varIndex = index - 1;
	double value = Evaluator::evaluate(arguments, &(++index), _symbolTable);
	_modifier->setVariableValue(arguments[varIndex], value);
	_modifier->updateSimulator(arguments[varIndex]);
	return index;
}