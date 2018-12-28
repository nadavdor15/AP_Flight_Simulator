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
	
	
	/*
	* doCommand ->
	* Opens a server on a different thread that the simulator connects to, and recieves messages from it
	* at a given speed.
	* */
	virtual int doCommand(vector<string>& arguments, unsigned int index);
  virtual ~DataReaderServer();
private:
	
	/*
	* opens a socket and waits for first signs from the simulator.
	* */
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
