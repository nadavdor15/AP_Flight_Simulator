#ifndef LOOP_COMMAND_H
#define LOOP_COMMAND_H

#include "Command.h"
#include "ConditionParser.h"

using namespace std;

class LoopCommand : public ConditionParser {
public:
	LoopCommand(map<string, double>* symbolTable,
				map<string, Expression*>* expressionMap);
	virtual int doCommand(vector<string>& arguments, unsigned int index);
};

#endif