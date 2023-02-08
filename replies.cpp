#include <string>

std::string	NO_REPLY() {
	return ("");
}

std::string	REPLY(std::string msg) {
	return (std::string(":") + HOSTNAME + " " + msg + "\n");
}

std::string	ERR_ALREADYREGISTRED() {
	return (REPLY(":Unauthorized command (already registered)"));
}

std::string	ERR_NEEDMOREPARAMS(std::string cmd) {
	return (REPLY(cmd + " :Not enough parameters"));
}

std::string	ERR_UNKNOWNCOMMAND(std::string cmd) {
	return (REPLY(cmd + " :Unknown command"));
}
