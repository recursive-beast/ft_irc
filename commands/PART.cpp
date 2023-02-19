#include "replies.hpp"
#include "commands.hpp"
#include "validation.hpp"
#include "utils.hpp"

static std::string	forEach(Message msg, Server *server, Client *client, std::string name) {
	Channel		*channel;
	std::string	reason;

	channel = server->getChannel(name);
	if (!channel)
		return (ERR_NOSUCHCHANNEL(client, name));
	if (!channel->isOn(client))
		return (ERR_NOTONCHANNEL(client, channel));
	if (msg.params.size() > 2)
		reason = msg.params[1];
	channel->broadcast(MSG_PART(client, channel, reason));
	channel->part(client);
	return (NO_REPLY());
}

std::string	PART(Message msg, Server *server, Client *client) {
	std::vector<std::string>	names;
	std::string					reply;

	if (!client->registered)
		return (ERR_NOTREGISTERED(client, msg.cmd));
	if (msg.params.size() < 1)
		return (ERR_NEEDMOREPARAMS(client, msg.cmd));
	names = split(msg.params[0], ",");
	names = filter(names, isnotempty);
	if (names.size() == 0)
		return (ERR_NEEDMOREPARAMS(client, msg.cmd));
	for (size_t i = 0; i < names.size(); i++) {
		reply = forEach(msg, server, client, names[i]);
		if (reply != NO_REPLY())
			client->write(reply);
	}
	return (NO_REPLY());
}
