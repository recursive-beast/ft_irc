#include "replies.hpp"
#include "commands.hpp"
#include "validation.hpp"
#include "utils.hpp"

static std::string	forEach(Message msg, Server *server, Client *client, std::string name) {
	Channel	*channel;

	if (name.length() == 0)
		return (NO_REPLY());
	channel = server->getChannel(name);
	if (!channel)
		return (ERR_NOSUCHCHANNEL(client, name));
	if (!channel->isOn(client))
		return (ERR_NOTONCHANNEL(client, name));
	if (msg.params.size() > 2)
		channel->broadcast(MSG_PART(client, channel, msg.params[1]));
	else
		channel->broadcast(MSG_PART(client, channel));
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
	for (size_t i = 0; i < names.size(); i++) {
		reply = forEach(msg, server, client, names[i]);
		if (reply != NO_REPLY())
			client->write(reply);
	}
	return (NO_REPLY());
}