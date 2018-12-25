#ifndef PRINT_COMMAND_H
#define PRINT_COMMAND_H
#include "Command.h"
#include "StringHelper.h"
#include <iostream>
#include <algorithm>

using namespace std;

class PrintCommand : public Command {

public:
	PrintCommand(map<string,double>* symbolTable);
	virtual int doCommand(vector<string>& arguments, unsigned int index);
};

#endif //	!PRINT_COMMAND_H