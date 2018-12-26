#ifndef CONDITION_PARSER_H
#define CONDITION_PARSER_H

#include "Command.h"
#include <map>
#include "Expression.h"

class ConditionParser : public Command {
	// vector<Command
	map<string, double>* _symbolTable;
	map<string, Expression*> _expressionMap;
  map<string, int> _operatorsMap;
public:
	ConditionParser(map<string, double>* symbolTable);
	virtual int doCommand(vector<string>& arguments, unsigned int index) = 0;

protected:
	bool conditionIsTrue(vector<string>& arguments);
	
};

#endif