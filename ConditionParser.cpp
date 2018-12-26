#include "ConditionParser.h"
#include "Evaluator.h"
#include <iostream>

using namespace std;

ConditionParser::ConditionParser(map<string, double>* symbolTable) {
	_symbolTable = symbolTable;
  _operatorsMap = {{"<", 1}, {"<=", 2}, {">", 3}, {">=", 4}, {"==", 5}, {"!=", 6}};
}

bool ConditionParser::conditionIsTrue(vector<string>& arguments) {
	// cout << "arg is: ";
	// for ( string s : arguments)
	// 	cout << "'" << s << "' ";
	// cout << endl;
	vector<string> firstOp;
	vector<string>::iterator itr = ++(arguments.begin());
	string operators = ",<=,<,>=,>,==,!=,";
	string seperator = ",";
	while (operators.find(seperator + *itr + seperator) == string::npos) {
		firstOp.push_back(*itr);
		++itr;
	}
	string oper = *itr;
	*itr++;
	// cout << "first op is: ";
	// for (string s : firstOp)
	// 	cout << "'" << s << "' ";
	// cout << endl;
	vector<string> secondOp;
	while ((*itr).compare("{") != 0) {
		secondOp.push_back(*itr);
		++itr;
	}
	// cout << "second op is: ";
	// for (string s : secondOp)
	// 	cout << "'" << s << "' ";
	// cout << endl;
	unsigned int dummyIndex = 0;
	double firstVal = Evaluator::evaluate(firstOp, &dummyIndex, _symbolTable);
	dummyIndex = 0;
	double secondVal = Evaluator::evaluate(secondOp, &dummyIndex, _symbolTable);
	cout << "first val: '" << firstVal << "'" << endl;
	cout << "operator is: '" << oper << "'" << endl;
	cout << "second val: '" << secondVal << "'" << endl;
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
  return false;
}