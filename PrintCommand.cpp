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
	int start = 0;
	int end = 0;
	if ((arguments.size() - 1) < _argumentsAmount)
		throw "Amount of arguments is lower than " + to_string(_argumentsAmount);
	do {
		string arg = arguments[++index];
		int arg_l = arg.length();
		if (StringHelper::startsWith(arg, "\"")) {
			arg = substr(1);
			while (!StringHelper::endsWith(arg, "\"") && index < arguments.size()) {
				cout << arg;
				arg = arguments[++index];
			}
			cout << arg.substr(0, arg_l - 2);
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