#include "Client.hpp"
#include "Channel.hpp"
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
	return (REPLY("001", client, ":Welcome to the Internet Relay Network " + client->getMask()));
}

std::string	ERR_NOTREGISTERED(Client *client, std::string cmd) {
	return (REPLY("451", client, cmd + " :You have not registered"));
}

std::string	MSG_NICK(Client *client, std::string newnick) {
	return (client->getMask() + " NICK :" + newnick + "\r\n");
}

std::string	ERR_NOSUCHCHANNEL(Client *client, std::string channel) {
	return (REPLY("403", client, channel + " :No such channel"));
}

std::string	ERR_NOTONCHANNEL(Client *client, Channel *channel) {
	return (REPLY("442", client, channel->name + " :You're not on that channel"));
}

std::string	MSG_PART(Client *client, Channel *channel, std::string message = "") {
	if (message.length() == 0)
		message = client->getNickname();
	return (client->getMask() + " PART " + channel->name + " :" + message + "\r\n");
}

std::string	RPL_TOPIC(Client *client, Channel *channel) {
	return (REPLY("332", client, channel->name + " :" + channel->topic));
}

std::string	RPL_NOTOPIC(Client *client, Channel *channel) {
	return (REPLY("331", client, channel->name + " :No topic is set"));
}

std::string	ERR_CHANOPRIVSNEEDED(Client *client, Channel *channel) {
	return (REPLY("482", client, channel->name + " :You're not channel operator"));
}

std::string	MSG_TOPIC(Client *client, Channel *channel) {
	return (client->getMask() + " TOPIC " + channel->name + " :" + channel->topic + "\r\n");
}
