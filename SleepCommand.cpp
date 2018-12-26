#include "StringHelper.h"
#include <stdio.h>

#define SHOULD_GET_SPACES ",+,-,*,/,<,<=,>,>=,!=,==,=,(,),{,},(),{},"

using namespace std;

void StringHelper::addSpaces(string& line) {
  	string needSpaces = string(SHOULD_GET_SPACES);
	for (unsigned int i = 0; (i + 1) < line.length(); i++) {
		if (line[i] == '\"')
			while (line[++i] != '\"') {}
		if (needSpaces.find(string(",") + line[i] + string(",")) != string::npos) {
        	line.insert(i + 1, " ");
        	line.insert(i, " ");
        	i+=2;
	  	}
	}
}

string StringHelper::getArgument(vector<string>& arguments) {
	string argument = "";
	for (string arg : arguments)
		argument += (arg + " ");
	return argument;
}

vector<string> StringHelper::split(string line, const char* delim) {
	vector<string> commands;
	unsigned int firstIndex;
	while ((firstIndex = line.find_first_of(delim)) < line.length()) {
		string word = line.substr(0, firstIndex);
		if (word.length())
			commands.push_back(word);
		line = line.substr(++firstIndex);
	}
	if (line.length())
		commands.push_back(line);
	return commands;
}