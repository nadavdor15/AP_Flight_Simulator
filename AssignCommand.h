#ifndef ASSIGN_COMMAND_H
#define ASSIGN_COMMAND_H

#include "Command.h"

using namespace std;

class AssignCommand : public Command {
	map<string, vector<string>>* _bindTable;

public:
	AssignCommand(map<string, double>* symbolTable, map<string, vector<string>>* bindTable);
	virtual int doCommand(vector<string>& arguments, unsigned int index);
};

#endif //	!ASSIGN_COMMAND_H