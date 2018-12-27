#include "ConnectCommand.h"
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <thread>
#include <malloc.h>

#define MAX_PORT_SIZE 65536
#define MIN_PORT_SIZE 1

ConnectCommand::ConnectCommand(map<string, double>* symbolTable) {
	_symbolTable = symbolTable;
	_argumentsAmount = 2;
	_client_fd = -1;
}

void ConnectCommand::startClient(const char* dst_addr) {
	close(_client_fd);
	struct sockaddr_in address;

	if ((_client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		cout << "Could not open client socket, CLI is terminated" << endl;
		exit(1);
	}

	address.sin_family = AF_INET;
    inet_aton(dst_addr, &address.sin_addr);
    address.sin_port = htons(_port);

    if (connect(_client_fd, (struct sockaddr*) &address, sizeof(address)) < 0) {
    	cout << "Could not connect, CLI is terminated" << endl;
    	exit(1);
    }
    cout << "Client socket is now connected to: " << address.sin_addr.s_addr << ", " << address.sin_port << endl;
}

int ConnectCommand::doCommand(vector<string>& arguments, unsigned int index) {
	if ((arguments.size() - 1) < _argumentsAmount)
		throw "Arguments amount is lower than " + to_string(_argumentsAmount);
	const char* ip_address = arguments[++index].c_str();
	_port = stoi(arguments[++index]);
	if (_port < MIN_PORT_SIZE || _port > MAX_PORT_SIZE)
		throw "Second argument must be in range of 1-65536";
	startClient(ip_address);
	return ++index;
}

void ConnectCommand::sendMessage(const string message) {
	char* msg = (char*) malloc((message.length() + 2)*sizeof(char));
	strcpy(msg, message.c_str());
	strcat(msg, "\r\n");
	cout << "we send: '" << msg << "'" << endl;
	send(_client_fd, msg, strlen(msg), 0);
	free(msg);
}

ConnectCommand::~ConnectCommand() {
	close(_client_fd);
}
