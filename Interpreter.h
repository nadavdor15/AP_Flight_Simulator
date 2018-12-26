#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <map>
#include "Expression.h"
#include "Evaluator.h"
#include <iostream>
#include "Modifier.h"

using namespace std;

class Interpreter {
private:
	map<string, Expression*>* _expressionsMap;
	map<string, double>* _symbolTable;
	map<string, string>* _pathToVar;
	map<string, string>* _varToPath;
	Modifier* _modifier;
	map<string, vector<string>>* _bindedVarTable;

public:
	Interpreter();
	static vector<string> lexer(string line);
	static bool isScriptFile(string& line);
	void parser(vector<string> line, int index, istream& stream);
	vector<string> parseBlock(vector<string>& line, int i, istream& stream);
	~Interpreter();

private:
	void setExpressionsMap();
};

#endif