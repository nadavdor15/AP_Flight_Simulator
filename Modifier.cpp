#include "Modifier.h"

using namespace std;

Modifier::Modifier(map<string, vector<string>>* bindedVarTable,
			 	   map<string, double>* symbolTable,
			 	   map<string, string>* varToPath,
			 	   ConnectCommand* connectCommand) {
	_bindedVarTable = bindedVarTable;
	_symbolTable = symbolTable;
	_varToPath = varToPath;
	_connectCommand = connectCommand;
}

/*
* sets a variable's value and all of it's binded variables values.
* */
void Modifier::setVariableValue(string var, double value) {
	_symbolTable->operator[](var) = value;
	vector<string> changeNeighbors(1, var);
	while (!changeNeighbors.empty()) {
		var = changeNeighbors.front();
		changeNeighbors.erase(changeNeighbors.end() - 1);
		vector<string> neighbors = _bindedVarTable->operator[](var);
		for (string neighbor : neighbors)
			if (_symbolTable->find(neighbor) != _symbolTable->end()) {
				if (_symbolTable->at(neighbor) != value) {
					_symbolTable->at(neighbor) = value;
					changeNeighbors.push_back(neighbor);
				}
			} else {

				// CHANGE_PATH_IN_SIMULATOR
			}
	}
}

/*
* sends the simulator the updated values.
* */
void Modifier::updateSimulator(string varName) {
	try {
		if (_varToPath->find(varName) != _varToPath->end()) {
			string query = "set " + _varToPath->at(varName) + " " + to_string(_symbolTable->at(varName));
			_connectCommand->sendMessage(query);
		}
	} catch (...) {
		throw "Could not update simulator";
	}
}
