#include <string>

std::string	NO_REPLY() {
	return ("");
}

std::string	ERR_ALREADYREGISTRED() {
	return (":Unauthorized command (already registered)\n");
}

std::string	ERR_NEEDMOREPARAMS(std::string cmd) {
	return (cmd + " :Not enough parameters\n");
}

std::string	ERR_UNKNOWNCOMMAND(std::string cmd) {
	return (cmd + " :Unknown command\n");
}
