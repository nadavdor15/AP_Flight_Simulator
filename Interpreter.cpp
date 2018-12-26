#include <fstream>
#include "Interpreter.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "AssignCommand.h"
#include "PrintCommand.h"
#include "CommandExpression.h"
#include "SleepCommand.h"
#include "IfCommand.h"
#include "ExitCommand.h"
#include "LoopCommand.h"
#include "StringHelper.h"
#define DELIM "\t "
#define BLOCK_COMMANDS ",while,if,"

using namespace std;

Interpreter::Interpreter() {
	_expressionsMap = new map<string, Expression*>();
	_symbolTable = new map<string, double>();
	_pathToVar = new map<string, string>();
	_varToPath = new map<string, string>();
	_bindedVarTable = new map<string, vector<string>>();
	_modifier = new Modifier(_bindedVarTable, _symbolTable);
	setExpressionsMap();
}

vector<string> Interpreter::lexer(string line) {
	return StringHelper::split(line, DELIM);
}

void Interpreter::parser(vector<string> line, int index, istream& stream) {
	for (unsigned int i = index; i < line.size();) {
		Expression* expression;
		string argument = StringHelper::getArgument(line);
		StringHelper::addSpaces(argument);
		line = StringHelper::split(argument, " ");
		try {
			if (_symbolTable->find(line[i]) != _symbolTable->end()) {
				++i;
				continue;
			}
			expression = _expressionsMap->at(line[i]);
			line = parseBlock(line, i, stream);
		} catch (...) {
			cout << "Could not resolve '" << line[i] << "'" << endl;
			i++;
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

vector<string> Interpreter::parseBlock(vector<string>& line, int i, istream& stream) {
	string seperator = ",";
	string blockCommands = string(BLOCK_COMMANDS);
	if (blockCommands.find(seperator + line[i] + seperator) != string::npos) {
		string untilBracket = "";
		string current = StringHelper::getArgument(line);
		int indentation = 0;
		do {
			untilBracket += current + " \n";
			if (current.find("{") != string::npos)
				++indentation;
			if (current.find("}") != string::npos)
				if (--indentation == 0)
					break;
		} while (getline(stream, current));
		line = lexer(untilBracket);
		string argument = StringHelper::getArgument(line);
		StringHelper::addSpaces(argument);
		return StringHelper::split(argument, " ");
	}
	return line;
}

void Interpreter::setExpressionsMap() {
	_expressionsMap->operator[]("openDataServer") = new CommandExpression(new OpenServerCommand(_symbolTable, _pathToVar, _bindedVarTable, _modifier));
	_expressionsMap->operator[]("connect") = new CommandExpression(new ConnectCommand(_symbolTable));
	_expressionsMap->operator[]("var") = new CommandExpression(new DefineVarCommand(_symbolTable, _expressionsMap));
	_expressionsMap->operator[]("=") = new CommandExpression(new AssignCommand(_symbolTable, _pathToVar, _bindedVarTable, _modifier));
	_expressionsMap->operator[]("print") = new CommandExpression(new PrintCommand(_symbolTable));
	_expressionsMap->operator[]("sleep") = new CommandExpression(new SleepCommand(_symbolTable));
	_expressionsMap->operator[]("if") = new CommandExpression(new IfCommand(_symbolTable, _expressionsMap));
	_expressionsMap->operator[]("while") = new CommandExpression(new LoopCommand(_symbolTable, _expressionsMap));
	_expressionsMap->operator[]("exit") = new CommandExpression(new ExitCommand());
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
	delete _pathToVar;
	delete _bindedVarTable;
	delete _varToPath;
	delete _modifier;
}