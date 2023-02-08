#include "Client.hpp"
#include <string>

std::string	NO_REPLY() {
	return ("");
}

// :<sender> <reply code> <receiver> <message>\r\n
std::string	REPLY(std::string reply_code, std::string receiver, std::string message) {
	if (receiver.empty())
		receiver = "*";
	return (std::string(":") + HOSTNAME + " " + reply_code + " " + receiver + " " + message + "\r\n");
}

std::string	ERR_ALREADYREGISTRED(std::string receiver) {
	return (REPLY("462", receiver, ":Unauthorized command (already registered)"));
}

std::string	ERR_NEEDMOREPARAMS(std::string receiver, std::string cmd) {
	return (REPLY("461", receiver, cmd + " :Not enough parameters"));
}

std::string	ERR_UNKNOWNCOMMAND(std::string receiver, std::string cmd) {
	return (REPLY("421", receiver, cmd + " :Unknown command"));
}
