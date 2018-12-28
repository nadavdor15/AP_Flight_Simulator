#include "ConditionParser.h"
#include "Evaluator.h"
#include "StringHelper.h"
#include <iostream>
#define MIN(a,b) (((a)<(b))?(a):(b))

#define DELIM "\n"

using namespace std;

ConditionParser::ConditionParser(map<string, double>* symbolTable,
                                 map<string, Expression*>* expressionsMap,
                                 Interpreter* interpreter) {
	_symbolTable = symbolTable;
  _expressionsMap = expressionsMap;
  _interpreter = interpreter;
  // sets operators map:
  _operatorsMap = {{"<", 1}, {"<=", 2}, {">", 3}, {">=", 4}, {"==", 5}, {"!=", 6}};
}

/*
 * function that calculates whether the condition
 * held by the condition parser is accurate.
 * */
bool ConditionParser::conditionIsTrue(vector<string>& arguments) {
	// finds out where is the condition in the arguments list.
	int ifIndex = StringHelper::nextIndexOf(arguments.begin(), "if", arguments.end());
	int whileIndex = StringHelper::nextIndexOf(arguments.begin(), "while", arguments.end());
	int startingIndex = MIN(ifIndex, whileIndex);
	vector<string>::iterator itr = ++(arguments.begin()) + startingIndex;
	string operators = ",<=,<,>=,>,==,!=,";
	string seperator = ",";
	// reads expression until an operator is found -> first operant.
	vector<string> firstOp;
	while (operators.find(seperator + *itr + seperator) == string::npos) {
		firstOp.push_back(*itr);
		++itr;
	}
	string oper = *itr;
	*itr++;
	// reads expression until an { is found -> second operant.
	vector<string> secondOp;
	while ((*itr).compare("{") != 0) {
		secondOp.push_back(*itr);
		++itr;
	}
	unsigned int dummyIndex = 0;
	double firstVal = Evaluator::evaluate(firstOp, &dummyIndex, _symbolTable);
	dummyIndex = 0;
	double secondVal = Evaluator::evaluate(secondOp, &dummyIndex, _symbolTable);
    switch (_operatorsMap.at(oper)) {
		case 1:
		  return firstVal < secondVal;
		  break;
		case 2:
		  return firstVal <= secondVal;
		  break;
		case 3:
		  return firstVal > secondVal;
		  break;
		case 4:
		  return firstVal >= secondVal;
		  break;
		case 5:
		  return firstVal == secondVal;
		  break;
		case 6:
		  return firstVal != secondVal;
		  break;
		default:
		  throw "Undefined comparison in condition";
  };
}

// function that calls parser on condition body's block.
void ConditionParser::runBlock(vector<string>& arguments) {
	_interpreter->parser(arguments, 0);
}

// extracts the block of commands from the condition.
vector<string> ConditionParser::extractBlock(vector<string>& vec) {
	int i = StringHelper::nextIndexOf(vec.begin(), "{", vec.end());
	auto itr = vec.begin() + i;
	int indentation = 0;
	vector<string> body;
	while (itr != vec.end()) {
		if (itr->find("{") != string::npos)
			++indentation;
		if (itr->find("}") != string::npos)
			if (--indentation == 0)
				break;
		body.push_back(*(++itr));
	}
 	body.pop_back();
 	return body;
}