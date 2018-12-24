#include "Command.h"
#include "StringHelper.h"
#include <iostream>
#include <algorithm>

using namespace std;

class PrintCommand : public Command {

public:
	PrintCommand(map<string,double>* symbolTable) {
		_symbolTable = symbolTable;
		_argumentsAmount = 1;
	}

	virtual int doCommand(vector<string>& arguments, unsigned int index) {
		if ((arguments.size() - 1) < _argumentsAmount)
			throw "Amount of arguments is lower than " + to_string(_argumentsAmount);
		do {
			string arg = arguments[++index];
			int arg_l = arg.length();
			if (arg[0] == '\"' && arg[arg_l - 1] == '\"') {
				arg = arg.substr(1, arg_l - 2);
				cout << arg << endl;
			}
			else {
				if (_symbolTable->find(arg) == _symbolTable->end())
					throw "The var " + arg + " is not defined";
				cout << _symbolTable->at(arg);
			}
		} while ((++index + 1) < arguments.size() && arguments[index] == "+");
		return index;
	}
};
