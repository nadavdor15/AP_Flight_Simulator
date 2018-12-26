#ifndef SLEEP_COMMAND_H
#define SLEEP_COMMAND_H
#include "Command.h"

class SleepCommand : public Command {
public:
	SleepCommand(map<string, double>* symbolTable);
	virtual int doCommand(vector<string>& arguments, unsigned int index);
};

#endif //    !SLEEP_COMMAND_H