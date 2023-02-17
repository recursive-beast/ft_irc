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

std::string	ERR_NOSUCHNICK(Client *client, std::string nickname) {
	return (REPLY("401", client, nickname + " :No such nick/channel"));
}

std::string	ERR_USERONCHANNEL(Client *client, Client *user, Channel *channel) {
	return (REPLY("443", client, user->getNickname() + " " + channel->name + " :is already on channel"));
}

std::string	RPL_INVITING(Client *client, Client *invited, Channel *channel) {
	return (REPLY("341", client, channel->name + " " + invited->getNickname()));
}

std::string	MSG_INVITE(Client *inviting, Client *invited, Channel *channel) {
	return (inviting->getMask() + " INVITE " + invited->getNickname() + " " + channel->name + "\r\n");
}

std::string	RPL_NAMREPLY(Client *client, Channel *channel) {
	std::string				message;
	std::vector<Client *>	members;
	Client					*member;

	message = "= " + channel->name + ":";
	members = channel->getMembers();
	for (size_t i = 0; i < members.size(); i++) {
		member = members[i];
		if (i)
			message += " ";
		if (channel->hasMode(CH_MODE_OPERATOR, member))
			message += "@";
		else if (channel->hasMode(CH_MODE_VOICE, member))
			message += "+";
		message += member->getNickname();
	}

	return (REPLY("353", client, message));
}

std::string	RPL_ENDOFNAMES(Client *client, Channel *channel) {
	return (REPLY("366", client, channel->name + " :End of NAMES list"));
}

std::string	RPL_LIST(Client *client, Channel *channel) {
	return (REPLY("322", client, channel->name + " " + std::to_string(channel->getCount()) + ":" + channel->topic));
}

std::string	RPL_LISTEND(Client *client) {
	return (REPLY("323", client, ":End of LIST"));
}
