#include "Client.hpp"
#include <string>

std::string	NO_REPLY() {
	return ("");
}

// :<sender> <reply code> <receiver> <message>\r\n
std::string	REPLY(std::string reply_code, Client *client, std::string message) {
	std::string	receiver;

	if (client)
		receiver = client->getNickname();
	if (receiver.empty())
		receiver = "*";
	return (std::string(":") + HOSTNAME + " " + reply_code + " " + receiver + " " + message + "\r\n");
}

std::string	BROADCAST_REPLY(std::string reply_code, std::string message) {
	return (REPLY(reply_code, NULL, message));
}

std::string	ERR_ALREADYREGISTRED(Client *client) {
	return (REPLY("462", client, ":Unauthorized command (already registered)"));
}

std::string	ERR_NEEDMOREPARAMS(Client *client, std::string cmd) {
	return (REPLY("461", client, cmd + " :Not enough parameters"));
}

std::string	ERR_UNKNOWNCOMMAND(Client *client, std::string cmd) {
	return (REPLY("421", client, cmd + " :Unknown command"));
}

std::string	ERR_NONICKNAMEGIVEN(Client *client) {
	return (REPLY("431", client, ":No nickname given"));
}

std::string	ERR_NICKNAMEINUSE(Client *client, std::string nick) {
	return (REPLY("433", client, nick + " :Nickname is already in use"));
}

std::string	ERR_ERRONEUSNICKNAME(Client *client, std::string nick) {
	return (REPLY("432", client, nick + " :Erroneous nickname"));
}

std::string	ERR_ERRONEUSUSERNAME(Client *client, std::string cmd) {
	return (REPLY("468", client, cmd + " :Your username is not valid"));
}

std::string	ERR_PASSWDMISMATCH(Client *client) {
	return (REPLY("464", client, ":Password incorrect"));
}

std::string	RPL_WELCOME(Client *client) {
	return (REPLY("001", client, ":Welcome to the Internet Relay Network " + client->getNickname() + "!" + client->username + "@" + client->addr));
}
