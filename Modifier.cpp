#include "Modifier.h"

using namespace std;

Modifier::Modifier(map<string, vector<string>>* bindedVarTable,
			 	   map<string, double>* symbolTable) {
	_bindedVarTable = bindedVarTable;
	_symbolTable = symbolTable;
}

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