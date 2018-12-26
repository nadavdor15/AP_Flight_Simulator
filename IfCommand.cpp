#include "IfCommand.h"

IfCommand::IfCommand(map<string, double>* symbolTable,
						 map<string, Expression*>* expressionMap):
						 ConditionParser(symbolTable) {
	
}

int IfCommand::doCommand(vector<string>& arguments, unsigned int index) {
	return arguments.size();
}