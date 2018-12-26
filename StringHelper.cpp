#include "StringHelper.h"
#include <string>
#include <vector>

using namespace std;

void StringHelper::addSpaces(string& line) {
  	string needSpaces = string(SHOULD_GET_SPACES);
	for (int i = 0; (i + 1) < line.length(); i++) {
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
	int firstIndex;
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

static bool StringHelper::endsWith(const string s, const string suffix) {
	int suffixLen = suffix.size();
	int sLen = s.size();
	if (s.size() < suffixLen)
		return false;
	else 
		return (s.compare(sLen - suffixLen, suffixLen, suffix) == 0);
}

static bool StringHelper::startsWith(const string s, const string prefix) {
	int prefixLen = prefix.size();
	int sLen = s.size();
	if (s.size() < prefixLen)
		return false;
	else 
		return (s.compare(0, prefixLen, prefix) == 0);
}