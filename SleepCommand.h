#ifndef SLEEP_COMMAND_H
#define SLEEP_COMMAND_H
#include "Command.h"
#include "Evaluator.h"
#include <unistd.h>
#define MILLI_IN_MICRO 1000

class SleepCommand :
	public Command
{
	Evaluator* evaluator;
public:

	SleepCommand(Evaluator* e)
	{
		(*this).evaluator = e;
		(*this)._argumentsAmount = 1;
	}
	virtual int doCommand(vector<string>& arguments, int index) {
		if ((arguments.size() - 1) < _argumentsAmount) {
			throw "Arguments amount is lower than " + to_string(_argumentsAmount);
		}
		unsigned argC = 0;
		double millisec = (*(*this).evaluator).evaluate(arguments, argC);
		usleep(millisec * MILLI_IN_MICRO);
		return 1 + argC;
	}
};

#endif //    !SLEEP_COMMAND_H
