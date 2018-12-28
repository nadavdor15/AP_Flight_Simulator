#include "LoopCommand.h"
#include "StringHelper.h"

using namespace std;

LoopCommand::LoopCommand(map<string, double>* symbolTable,
                  			 map<string, Expression*>* expressionsMap,
                         Interpreter* interpreter):
                  			 ConditionParser(symbolTable, expressionsMap, interpreter) {
  _argumentsAmount = 5;
}

/*
* extracts it's block of commands and runs it while condition is true.
* */
int LoopCommand::doCommand(vector<string>& arguments, unsigned int index) {
  if ((arguments.size() - 1 - index) < _argumentsAmount)
  	throw "Amount of arguments is lower than " + to_string(_argumentsAmount);
  while (this->conditionIsTrue(arguments)) {
    vector<string> argumentsOnly = extractBlock(arguments);
    this->runBlock(argumentsOnly);
  }
  return StringHelper::nextIndexOf(arguments.begin(), "}", arguments.end()) + 1;
}
