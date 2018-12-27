#ifndef CONDITION_PARSER_H
#define CONDITION_PARSER_H

#include "Command.h"
#include <map>
#include "Expression.h"
#include "Interpreter.h"

#define PAIR pair<Expression*, vector<string>>;

class ConditionParser : public Command {
	Interpreter* _interpreter;
	map<string, double>* _symbolTable;
	map<string, Expression*>* _expressionsMap;
  	map<string, int> _operatorsMap;
public:
	ConditionParser(map<string, double>* symbolTable,
					map<string, Expression*>* expressionsMap,
					Interpreter* interpreter);
	virtual int doCommand(vector<string>& arguments, unsigned int index) = 0;

protected:
	bool conditionIsTrue(vector<string>& arguments);
    void runBlock(vector<string>& arguments);
    vector<string> extractBlock(vector<string>& vec);
};

#endif