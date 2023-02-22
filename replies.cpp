#include "Client.hpp"
#include "Channel.hpp"
#include "utils.hpp"
#include <string>

std::string	NO_REPLY() {
	return ("");
}

// :<sender> <reply code> <receiver> <message>\r\n
static std::string	REPLY(std::string reply_code, Client *client, std::string message) {
	std::string	receiver;

	if (client)
		receiver = client->getNickname();
	if (receiver.empty())
		receiver = "*";
	return (std::string(":") + HOSTNAME + " " + reply_code + " " + receiver + " " + message + "\r\n");
}

static std::string	MSG(Client *client, std::string cmd, std::string message = "") {
	std::string	result;

	result = ":" + client->getMask() + " " + cmd;
	if (!message.empty())
		result += + " " + message;
	result += "\r\n";
	return (result);
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
	return (MSG(client, "NICK", newnick));
}

std::string	ERR_NOSUCHCHANNEL(Client *client, std::string channel) {
	return (REPLY("403", client, channel + " :No such channel"));
}

std::string	ERR_NOTONCHANNEL(Client *client, Channel *channel) {
	return (REPLY("442", client, channel->name + " :You're not on that channel"));
}

std::string	MSG_PART(Client *client, Channel *channel, std::string reason = "") {
	if (reason.length() == 0)
		reason = client->getNickname();
	return (MSG(client, "PART", channel->name + " :" + reason));
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

std::string	ERR_NOPRIVILEGES(Client *client) {
	return (REPLY("481", client, ":Permission Denied- You're not an IRC operator"));
}

std::string	MSG_TOPIC(Client *client, Channel *channel) {
	return (MSG(client, "TOPIC", channel->name + " :" + channel->topic));
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
	return (MSG(inviting, "INVITE", invited->getNickname() + " " + channel->name));
}

std::string	RPL_NAMREPLY(Client *client, Channel *channel) {
	std::string				message;
	std::vector<Client *>	members;
	Client					*member;

	message = "= " + channel->name + " :";
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

std::string	MSG_KICK(Client *client, Channel *channel, std::string reason = "") {
	if (reason.length() == 0)
		reason = client->getNickname();
	return (MSG(client, "KICK", channel->name + " :" + reason));
}

std::string	ERR_USERNOTINCHANNEL(Client *client, Channel *channel, std::string nickname) {
	return (REPLY("441", client, nickname + " " + channel->name + " :They aren't on that channel"));
}

std::string	ERR_BADCHANMASK(Client *client, std::string channel) {
	return (REPLY("476", client, channel + " :Bad Channel Mask"));
}

std::string	ERR_KEYSET(Client *client, Channel *channel) {
	return (REPLY("467", client, channel->name + " :Channel key already set"));
}

std::string	ERR_CHANNELISFULL(Client *client, Channel *channel) {
	return (REPLY("471", client, channel->name + " :Cannot join channel (+l)"));
}

std::string	ERR_UNKNOWNMODE(Client *client, Channel *channel, char mode) {
	std::string	message;

	message += mode;
	message += " :is unknown mode char to me for " + channel->name;
	return (REPLY("472", client, message));
}

std::string	ERR_INVITEONLYCHAN(Client *client, Channel *channel) {
	return (REPLY("473", client, channel->name + " :Cannot join channel (+i)"));
}

std::string	ERR_BANNEDFROMCHAN(Client *client, Channel *channel) {
	return (REPLY("474", client, channel->name + " :Cannot join channel (+b)"));
}

std::string	ERR_BADCHANNELKEY(Client *client, Channel *channel) {
	return (REPLY("475", client, channel->name + " :Cannot join channel (+k)"));
}

std::string	ERR_BADCHANMASK(Client *client, Channel *channel) {
	return (REPLY("476", client, channel->name + " :Bad Channel Mask"));
}

std::string	ERR_NOCHANMODES(Client *client, Channel *channel) {
	return (REPLY("477", client, channel->name + " :Channel doesn't support modes"));
}

std::string	MSG_JOIN(Client *client, Channel *channel) {
	return (MSG(client, "JOIN", channel->name));
}

std::string	MSG_MODE(Client *client, Channel *channel) {
	return (MSG(client, "MODE", channel->name + " +" + join(channel->modes)));
}

std::string RPL_CHANNELMODEIS(Client *client, Channel *channel) {
	std::set<char>				modes = channel->modes;
	std::vector<std::string>	params;
	std::set<char>::iterator	it = modes.begin();
	std::string					msg;

	for (; it != modes.end() ; it++)
	{
		if (*it == CH_MODE_LIMIT)
			params.push_back(std::to_string(channel->limit));
		if (*it == CH_MODE_KEY)
			params.push_back(channel->key);
	}
	msg = channel->name + " +" + join(channel->modes);
	if (params.size())
		msg += " " + join(params, " ");
	return (MSG(client, "MODE", msg));
}

std::string	MSG_QUIT(Client *client, std::string reason = "") {
	return (MSG(client, "QUIT", reason));
}
