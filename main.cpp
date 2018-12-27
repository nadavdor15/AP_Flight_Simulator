#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Interpreter.h"

using namespace std;

int main(int argc, char* argv[]) {
	Interpreter interpreter;
	vector<string> endProgram = {"exit"};

	string inputStr;
	if (argc == 2) {
		ifstream script(argv[1]);
		interpreter.setStream(script);
		while (getline(script, inputStr)) {
			vector<string> line = Interpreter::lexer(inputStr);
			interpreter.parser(line, 0);
		}
		return 0;
	}
	while (getline(cin, inputStr)) {
		if (Interpreter::isScriptFile(inputStr)) {
			ifstream script(inputStr);
			interpreter.setStream(script);
			while (getline(script, inputStr)) {
				vector<string> line = Interpreter::lexer(inputStr);
				interpreter.parser(line, 0);
			}
			interpreter.parser(endProgram, 0);
		}
		vector<string> line = Interpreter::lexer(inputStr);
		interpreter.parser(line, 0);
	}
}