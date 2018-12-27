#ifndef IF_COMMAND_H
#define IF_COMMAND_H

#include "Command.h"
#include "ConditionParser.h"
#include "Interpreter.h"

using namespace std;

class IfCommand : public ConditionParser {
public:
	IfCommand(map<string, double>* symbolTable,
				map<string, Expression*>* expressionsMap,
				Interpreter* interpreter);
	virtual int doCommand(vector<string>& arguments, unsigned int index);
};

#endif