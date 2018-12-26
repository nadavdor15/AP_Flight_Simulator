
#ifndef STRING_HELPER_H
#define STRING_HELPER_H

#include <vector>
#include <string>

using namespace std;

class StringHelper {
public:
	static void addSpaces(string& line);
	static string getArgument(vector<string>& arguments);
	static vector<string> split(string line, const char* delim);
	static bool endsWith(const string s, const string suffix);
	static bool startsWith(const string s, const string prefix);
};

#endif