#ifndef DATA_READER_SERVER_H
#define DATA_READER_SERVER_H

#include "Command.h"

using namespace std;

class DataReaderServer : public Command {
	map<string, vector<string>>* _bindTable;
public:

	DataReaderServer(map<string,double>* symbolTable,
					 map<string, vector<string>>* bindTable);
	virtual int doCommand(vector<string>& arguments, unsigned int index);

private:
	static void startServer(int port, 
							unsigned int speed,
							map<string,double>* symbolTable, 
							map<string, vector<string>>* bindTable);
	static void updateVars(vector<double> values,
						   map<string,double>* symbolTable,
						   map<string, vector<string>>* bindTable,
						   vector<string>& names);
	static vector<string> getNames();
};

#endif	//	!DATA_READER_SERVER_H