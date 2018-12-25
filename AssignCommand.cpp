#include "AssignCommand.h"
#include "StringHelper.h"
#include "Evaluator.h"

AssignCommand::AssignCommand(map<string, double>* symbolTable, map<string, vector<string>>* bindTable) {
	_symbolTable = symbolTable;
	_bindTable = bindTable;
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
			if (path[0] != '\"' || path[path_length - 1] != '\"')
				throw "Path should be in quatation marks";
			path = path.substr(1, path_length - 2);
			_bindTable->operator[](path).push_back(arguments[index - 1]);
			return index + 3;
		}
	}
	int varIndex = index - 1;
	double value = Evaluator::evaluate(arguments, &(++index), _symbolTable);
	_symbolTable->operator[](arguments[varIndex]) = value;
	return index;
}