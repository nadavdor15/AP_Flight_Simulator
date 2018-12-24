#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>
#include <map>
#include "Evaluator.h"

using namespace std;

class Command {
protected:
	unsigned int _argumentsAmount;
	map<string, double>* _symbolTable;

public:
	virtual int doCommand(vector<string>& arguments, unsigned int index) = 0;

	virtual ~Command() {}
};

#endif