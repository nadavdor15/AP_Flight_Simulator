#include "LoopCommand.h"

LoopCommand::LoopCommand(map<string, double>* symbolTable,
						 map<string, Expression*>* expressionMap):
						 ConditionParser(symbolTable) {

}

int LoopCommand::doCommand(vector<string>& arguments, unsigned int index) {
	if (this->conditionIsTrue(arguments))
		cout << "TRUEEEEEEEEEEEE" << endl;
  return arguments.size();
}