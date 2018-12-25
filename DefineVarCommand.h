#ifndef DEFINE_VAR_COMMAND_H
#define DEFINE_VAR_COMMAND_H

#include "Command.h"

using namespace std;

class DefineVarCommand : public Command {
	map<string, Expression*>* _savedNames;

public:
	DefineVarCommand(map<string, double>* symbolTable, map<string, Expression*>* savedNames);
	virtual int doCommand(vector<string>& arguments, unsigned int index);

private:
	void checkValidity(string varName);
};

#endif	//	!DEFINE_VAR_COMMAND_H