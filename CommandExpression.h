#ifndef COMMAND_EXPRESSION_H
#define COMMAND_EXPRESSION_H

#include <iostream>
#include "Expression.h"
#include "Command.h"

using namespace std;

/*
 * Class that adapts a Command as an Expression object.
 * */
class CommandExpression : public Expression {
	Command* _command;

public:
	CommandExpression() {}

	CommandExpression(Command* command) {
		_command = command;
	}

	virtual double calculate(vector<string>& arguments, int index) {
		return _command->doCommand(arguments, index);
	}

	~CommandExpression() {
		delete _command;
	}
};

#endif //	COMMAND_EXPRESSION_H