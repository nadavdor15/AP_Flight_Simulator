#include "ConnectCommand.h"
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <thread>
#include <malloc.h>
#include <stdio.h>

#define MAX_PORT_SIZE 65536
#define MIN_PORT_SIZE 1

ConnectCommand::ConnectCommand(map<string, double>* symbolTable) {
	_symbolTable = symbolTable;
	_argumentsAmount = 2;
	_client_fd = -1;
}

/*
 * function that starts the connection between the simulator and program
 * as clients.
*/
void ConnectCommand::startClient(const char* dst_addr) {
	close(_client_fd);
	struct sockaddr_in address;
	// tries to open a socket
	if ((_client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		cout << "Could not open client socket, CLI is terminated" << endl;
		exit(1);
	}
	// sets socket's attributes.
	address.sin_family = AF_INET;
	inet_aton(dst_addr, &address.sin_addr);
	address.sin_port = htons(_port);
	// tries to connect to simulator
	if (connect(_client_fd, (struct sockaddr*) &address, sizeof(address)) < 0) {
		cout << "Could not connect, CLI is terminated" << endl;
		exit(1);
}
//cout << "Client socket is now connected to: " << address.sin_addr.s_addr << ", " << address.sin_port << endl;
}

/*
 * do Command reads the arguments and sets the connection
 * between the simulator.
 * */
int ConnectCommand::doCommand(vector<string>& arguments, unsigned int index) {
	if ((arguments.size() - 1) < _argumentsAmount)
		throw "Arguments amount is lower than " + to_string(_argumentsAmount);
	const char* ip_address = arguments[++index].c_str();
	_port = (int) Evaluator::evaluate(arguments, &(++index), _symbolTable);
	if (_port < MIN_PORT_SIZE || _port > MAX_PORT_SIZE)
		throw "Second argument must be in range of 1-65536";
	startClient(ip_address);
	return ++index;
}

void ConnectCommand::sendMessage(const string message) {
	char* msg = NULL;
	while (msg == NULL)
		msg = (char*) malloc((message.length() + 3)*sizeof(char));
	strcpy(msg, message.c_str());
	strcat(msg, "\r\n");
	send(_client_fd, msg, strlen(msg), 0);
	free(msg);
}

ConnectCommand::~ConnectCommand() {
	close(_client_fd);
}
