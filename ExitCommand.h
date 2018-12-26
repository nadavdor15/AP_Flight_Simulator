#ifndef EXIT_COMMAND
#define EXIT_COMMAND

#include "Command.h"
#include <vector>

using namespace std;

class ExitCommand {
	// no members.
public:
	
	ExitCommand() {}

	virtual int doCommand(vector<string>& arguments, unsigned int index) {
		exit(0);
		return 0;
	}

	virtual ~Command() {}
}

#endif //	!EXIT_COMMAND
