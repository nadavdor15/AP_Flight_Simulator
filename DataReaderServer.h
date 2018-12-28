#ifndef DATA_READER_SERVER_H
#define DATA_READER_SERVER_H

#include "Command.h"
#include "Modifier.h"

using namespace std;

class DataReaderServer : public Command {
	map<string, string>* _pathToVar;
	Modifier* _modifier;
  	int _sockID;
  	int _port;
public:

	DataReaderServer(map<string,double>* symbolTable,
					 map<string, string>* pathToVar,
					 map<string, vector<string>>* bindedVarTable,
					 Modifier* modifier);
	virtual int doCommand(vector<string>& arguments, unsigned int index);
  virtual ~DataReaderServer();
private:
  void openSocket();
	static void startServer(int new_socket,
            unsigned int speed,
						map<string,double>* symbolTable,
						map<string, string>* pathToVar,
						Modifier* modifier);
	static void updateVars(vector<double> values,
						   Modifier* modifier,
						   map<string, string>* pathToVar,
						   vector<string>& names);
	static vector<string> getNames();
};

#endif	//	!DATA_READER_SERVER_H