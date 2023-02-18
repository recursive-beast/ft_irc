#include "replies.hpp"
#include "commands.hpp"
#include "validation.hpp"
#include "utils.hpp"

static std::string	forEach(
	Message msg,
	Server *server,
	Client *client,
	std::string chname,
	std::string nickname
) {
	Channel	*channel;
	Client	*target;

	channel = server->getChannel(chname);
	if (!channel)
		return (ERR_NOSUCHCHANNEL(client, chname));
	if (!channel->isOn(client))
		return (ERR_NOTONCHANNEL(client, channel));
	if (!channel->hasMode(CH_MODE_OPERATOR, client))
		return (ERR_CHANOPRIVSNEEDED(client, channel));
	target = channel->getMember(nickname);
	if (!target)
		return (ERR_USERNOTINCHANNEL(client, channel, nickname));
	if (target == client)
		return (NO_REPLY());
	channel->part(target);
	if (msg.params.size() > 2)
		channel->broadcast(MSG_KICK(client, channel, msg.params[2]));
	else
		channel->broadcast(MSG_KICK(client, channel));
	target->write(MSG_PART(client, channel));
	return (NO_REPLY());
}

static void	manyInOne(
	Message msg,
	Server *server,
	Client *client,
	std::string chname,
	std::vector<std::string> nicknames
) {
	std::string	reply;

	for (size_t i = 0; i < nicknames.size(); i++) {
		reply = forEach(msg, server, client, chname, nicknames[i]);
		if (reply != NO_REPLY())
			client->write(reply);
	}
}

static void	manyInMany(
	Message msg,
	Server *server,
	Client *client,
	std::vector<std::string> chnames,
	std::vector<std::string> nicknames
) {
	std::string	reply;

	for (size_t i = 0; i < nicknames.size(); i++) {
		reply = forEach(msg, server, client, chnames[i], nicknames[i]);
		if (reply != NO_REPLY())
			client->write(reply);
	}
}

std::string	KICK(Message msg, Server *server, Client *client) {
	std::vector<std::string>	chnames;
	std::vector<std::string>	nicknames;
	std::string					reply;

	if (!client->registered)
		return (ERR_NOTREGISTERED(client, msg.cmd));
	if (msg.params.size() < 2)
		return (ERR_NEEDMOREPARAMS(client, msg.cmd));
	chnames = split(msg.params[0], ",");
	chnames = filter(chnames, isnotempty);
	nicknames = split(msg.params[1], ",");
	nicknames = filter(chnames, isnotempty);
	if (chnames.size() == 0 || nicknames.size() == 0)
		return (ERR_NEEDMOREPARAMS(client, msg.cmd));
	if (chnames.size() == 1) {
		manyInOne(msg, server, client, chnames[0], nicknames);
	} else {
		if (chnames.size() != nicknames.size())
			return (ERR_NEEDMOREPARAMS(client, msg.cmd));
		manyInMany(msg, server, client, chnames, nicknames);
	}
	return (NO_REPLY());
}
