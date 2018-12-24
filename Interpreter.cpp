#include <fstream>
#include <iostream>
#include "Interpreter.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "AssignCommand.h"
#include "PrintCommand.h"
#include "CommandExpression.h"
#include "StringHelper.h"
#define DELIM "\t "

using namespace std;

Interpreter::Interpreter() {
	_expressionsMap = new map<string, Expression*>();
	_symbolTable = new map<string, double>();
	_bindTable = new map<string, vector<string>>();
	_evaluator = new Evaluator(_symbolTable);
	setExpressionsMap();
}

vector<string> Interpreter::lexer(string line) {
	return StringHelper::split(line, DELIM);
}

void Interpreter::parser(vector<string> line, int index) {
	for (int i = index; i < line.size(); i++) {
		Expression* expression;
		string argument = StringHelper::getArgument(line);
		StringHelper::addSpaces(argument);
		line = StringHelper::split(argument, " ");
		try {
			if (_symbolTable->find(line[i]) != _symbolTable->end())
				continue;
			expression = _expressionsMap->at(line[i]);
		} catch (...) {
			cout << "Could not resolve '" << line[i] << "'" << endl;
			break;
		}
		try {
			i = (int) expression->calculate(line, i);
		} catch (string e) {
			cout << e << endl;
			break;
		} catch (char const* e) {
			cout << e << endl;
			break;
		}
	}
}

void Interpreter::setExpressionsMap() {
	_expressionsMap->operator[]("openDataServer") = new CommandExpression(new OpenServerCommand(_symbolTable, _bindTable), _evaluator);
	_expressionsMap->operator[]("connect") = new CommandExpression(new ConnectCommand(_symbolTable), _evaluator);
	_expressionsMap->operator[]("var") = new CommandExpression(new DefineVarCommand(_symbolTable, _expressionsMap), _evaluator);
	_expressionsMap->operator[]("=") = new CommandExpression(new AssignCommand(_symbolTable, _bindTable), _evaluator);
	_expressionsMap->operator[]("print") = new CommandExpression(new PrintCommand(_symbolTable), _evaluator);
}

bool Interpreter::isScriptFile(string& line) {
	bool flag;
	vector<string> words = StringHelper::split(line, DELIM);
	if (words.size() != 2)
		return false;
	if (words[0].compare("run") != 0)
		return false;
	line = words[1].substr(1, words[1].length() - 2);
	ifstream file(line);
	flag = (bool) file;
	file.close();
	return flag;
}

Interpreter::~Interpreter() {
	for (auto it = _expressionsMap->begin(); it != _expressionsMap->end(); it++)
		delete it->second;
	delete _expressionsMap;
	delete _symbolTable;
	delete _bindTable;
	delete _evaluator;
}