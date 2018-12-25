#include "PrintCommand.h"
#include "StringHelper.h"
#include <iostream>
#include <algorithm>

using namespace std;

PrintCommand::PrintCommand(map<string,double>* symbolTable) {
	_symbolTable = symbolTable;
	_argumentsAmount = 1;
}

int PrintCommand::doCommand(vector<string>& arguments, unsigned int index) {
	if ((arguments.size() - 1) < _argumentsAmount)
		throw "Amount of arguments is lower than " + to_string(_argumentsAmount);
	do {
		string arg = arguments[++index];
		int arg_l = arg.length();
		if (arg[0] == '\"' && arg[arg_l - 1] == '\"') {
			arg = arg.substr(1, arg_l - 2);
			cout << arg;
		}
		else {
			if (_symbolTable->find(arg) == _symbolTable->end())
				throw "The var " + arg + " is not defined";
			cout << _symbolTable->at(arg);
		}
	} while ((++index + 1) < arguments.size() && arguments[index] == "+");
	cout << endl;
	return index;
}