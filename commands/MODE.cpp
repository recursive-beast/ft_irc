#include "replies.hpp"
#include "commands.hpp"
#include "validation.hpp"
#include "Channel.hpp"
#include <string>

bool	isPlusOrMinus(std::string& modes) {
	return (modes[0] == '+' || modes[0] == '-');
}

void	addMode(Channel *channel, Client *client, char mode, bool isOp, std::string parms) {
	switch (mode)
	{
		case CH_MODE_INVITE_ONLY:
			channel->setMode(mode);
			break;
		case CH_MODE_MODERATED:
			channel->setMode(mode);
			break;
		case CH_MODE_NO_OUTSIDE:
			channel->setMode(mode);
			break;
		case CH_MODE_TOPIC:
			if (isOp) {
				channel->setMode(mode);
				channel->topic = parms;
			}
			break;
		case CH_MODE_KEY:
			if (isOp) {
				channel->setMode(mode);
				channel->key = parms;
			}
			break;
		case CH_MODE_LIMIT:
			if (isOp) {
				channel->setMode(mode);
				channel->limit = std::stoi(parms);
			}
			break;
		case CH_MODE_CREATOR:
			channel->setMode(mode);
			break;
		case CH_MODE_OPERATOR:
			channel->setMode(mode);
			channel->topic = parms;
			break;
		case CH_MODE_VOICE:
			if (isOp) {
				channel->setMode(mode, client);
				channel->topic = parms;
			}
			break;
		default:

			break;
	}
}

void	removeMode(Channel *channel, Client *client, char mode, bool isOp, std::string parms) {
	switch (mode)
	{
		case CH_MODE_INVITE_ONLY:
			channel->unsetMode(mode);
			break;
		case CH_MODE_MODERATED:
			channel->unsetMode(mode);
			break;
		case CH_MODE_NO_OUTSIDE:
			channel->unsetMode(mode);
			break;
		case CH_MODE_TOPIC:
			if (isOp) {
				channel->unsetMode(mode);
				channel->topic = "";
			}
			break;
		case CH_MODE_KEY:
			if (isOp && channel->key = parms) {
				channel->unsetMode(mode);
				channel->key = "";
			}
			break;
		case CH_MODE_LIMIT:
			if (isOp)
				channel->unsetMode(mode);
			break;
		case CH_MODE_CREATOR:
			channel->unsetMode(mode, client);
			break;
		case CH_MODE_OPERATOR:
			channel->unsetMode(mode, client);
			channel->topic = parms;
			break;
		case CH_MODE_VOICE:
			if (isOp) {
				channel->unsetMode(mode, client);
				channel->topic = parms;
			}
			break;
		default:

			break;
	}
}

std::string	MODE(Message msg, Server *server, Client *client) {
	Channel *channel;

	if (!client->registered)
		return (ERR_NOTREGISTERED(client, msg.cmd));
	if (msg.params.size() < 1)
		return (ERR_NEEDMOREPARAMS(client, msg.cmd));
	if (!server->getChannel(msg.params[0]))
		return (ERR_NOSUCHCHANNEL(client, msg.params[0]));
	channel = server->getChannel(msg.params[0]);
	if (msg.params.size() < 2) {
		return (RPL_CHANNELMODEIS(client, channel));
	} else {
		bool	isPlus = false;

	}
}

