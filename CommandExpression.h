#ifndef COMMAND_EXPRESSION_H
#define COMMAND_EXPRESSION_H

#include <iostream>
#include "Expression.h"
#include "Command.h"
#include "Evaluator.h"

using namespace std;

class CommandExpression : public Expression {
	Command* _command;
	Evaluator* _evaluator;

public:
	CommandExpression() {}

	CommandExpression(Command* command, Evaluator* evaluator) {
		_command = command;
		_evaluator = evaluator;
	}

	virtual double calculate(vector<string>& arguments, int index) {
		return _command->doCommand(arguments, index);
	}

	~CommandExpression() {
		delete _command;
	}
};

#endif