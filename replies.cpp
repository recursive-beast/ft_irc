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

std::string	ERR_NONICKNAMEGIVEN(std::string receiver) {
	return (REPLY("431", receiver, ":No nickname given"));
}

std::string	ERR_NICKNAMEINUSE(std::string receiver, std::string nick) {
	return (REPLY("433", receiver, nick + " :Nickname is already in use"));
}

std::string	ERR_ERRONEUSNICKNAME(std::string receiver, std::string nick) {
	return (REPLY("432", receiver, nick + " :Erroneous nickname"));
}
