#include "replies.hpp"
#include "commands.hpp"
#include "validation.hpp"
#include "Channel.hpp"

std::string	TOPIC(Message msg, Server *server, Client *client) {
	Channel	*channel;

	if (!client->registered)
		return (ERR_NOTREGISTERED(client, msg.cmd));
	if (msg.params.size() < 1)
		return (ERR_NEEDMOREPARAMS(client, msg.cmd));
	channel = server->getChannel(msg.params[0]);
	if (!channel)
		return (ERR_NOSUCHCHANNEL(client, msg.params[0]));
	if (msg.params.size() == 1)
		return (RPL_TOPIC(client, channel));
	if (!channel->hasMode(CH_MODE_OPERATOR, client))
		return (ERR_CHANOPRIVSNEEDED(client, channel));
	if (channel->topic == msg.params[1])
		return (NO_REPLY());
	channel->topic = msg.params[1];
	channel->broadcast(MSG_TOPIC(client, channel));
	return (NO_REPLY());
}
