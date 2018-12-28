#include "PrintCommand.h"
#include "Evaluator.h"
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
	string printable = "nothing";
	do {
		string arg = arguments[++index];
		int arg_l = arg.length();
		if (StringHelper::startsWith(arg, "\"")) {
			arg = arg.substr(1);
			while (!StringHelper::endsWith(arg, "\"") && index < arguments.size()) {
				printable = arg + " ";
				cout << printable;
				arg = arguments[++index];
			}
     		arg_l = arg.length();
     		printable = arg.substr(0, arg_l - 1);
     		++index;
		} else {
			try {
				printable = to_string(Evaluator::evaluate(arguments, &index, _symbolTable));
			} catch (...) {
				throw "YOU CANNOT COMBINE DOUBLE WITH STRING!";
			}
		}
		cout << printable;
	} while ((index + 1) < arguments.size() && arguments[index] == "+");
	cout << endl;
	return index;
}