#include "replies.hpp"
#include "commands.hpp"
#include "validation.hpp"
#include "Channel.hpp"
#include <string>

#include <iostream>
std::string	applyMode(Channel *channel, Client *client, char mode, char op, std::string param) {
	Client	*to_apply;

	switch (mode)
	{
		case CH_MODE_INVITE_ONLY:
		case CH_MODE_MODERATED:
		case CH_MODE_NO_OUTSIDE:
		case CH_MODE_TOPIC:
			if (op == '+') {
				channel->setMode(mode);
				channel->broadcast(RPL_CHANNELMODEIS(client, channel));
			}
			else if (op == '-') {
				channel->unsetMode(mode);
				channel->broadcast(RPL_CHANNELMODEIS(client, channel));
			}
			return (NO_REPLY());
		case CH_MODE_KEY:
			if (op == '+') {
				channel->key = param;
				channel->setMode(mode);
				channel->broadcast(RPL_CHANNELMODEIS(client, channel));
			}
			else if (op == '-') {
				channel->unsetMode(mode);
				channel->broadcast(RPL_CHANNELMODEIS(client, channel));
			}
			return (NO_REPLY());
		case CH_MODE_LIMIT:
			if (op == '+') {
				try {
					channel->limit = std::stoi(param);
				} catch (...) {
					return (NO_REPLY());
				}
				channel->setMode(mode);
				channel->broadcast(RPL_CHANNELMODEIS(client, channel));
			}
			else if (op == '-') {
				channel->unsetMode(mode);
				channel->broadcast(RPL_CHANNELMODEIS(client, channel));
			}
			return (NO_REPLY());
		case CH_MODE_CREATOR:
			if (op == '+') {
				channel->setMode(mode);
			}
			else if (op == '-') {
				channel->unsetMode(mode);
			}
			return (ERR_NOPRIVILEGES(client));
			break;
		case CH_MODE_OPERATOR:
			to_apply = channel->getMember(param);
			if (op == '+') {
				if (to_apply) {
					channel->setMode(mode, to_apply);
					channel->broadcast(RPL_CHANNELMODEIS(client, channel));
				}
				else
					return (ERR_USERNOTINCHANNEL(client, channel, param));
			}
			else if (op == '-') {
				if (to_apply) {
					channel->unsetMode(mode, to_apply);
					channel->broadcast(RPL_CHANNELMODEIS(client, channel));
				}
				else
					return (ERR_USERNOTINCHANNEL(client, channel, param));
			}
			return (NO_REPLY());
		case CH_MODE_VOICE:
			to_apply = channel->getMember(param);
			if (op == '+') {
				if (to_apply) {
					channel->setMode(mode, to_apply);
					channel->broadcast(RPL_CHANNELMODEIS(client, channel));
				}
				else
					return (ERR_USERNOTINCHANNEL(client, channel, param));
			}
			else if (op == '-') {
				if (to_apply) {
					channel->unsetMode(mode, to_apply);
					channel->broadcast(RPL_CHANNELMODEIS(client, channel));
				}
				else
					return (ERR_USERNOTINCHANNEL(client, channel, param));
			}
			return (NO_REPLY());
		default:
			return (ERR_UNKNOWNMODE(client, channel, mode));
	}
}

std::string	MODE(Message msg, Server *server, Client *client) {
	Channel 	*channel;

	if (!client->registered)
		return (ERR_NOTREGISTERED(client, msg.cmd));
	if (msg.params.size() < 1)
		return (ERR_NEEDMOREPARAMS(client, msg.cmd));
	channel = server->getChannel(msg.params[0]);
	if (!channel)
		return (ERR_NOSUCHCHANNEL(client, msg.params[0]));
	if (!channel->isOn(client))
		return (ERR_NOTONCHANNEL(client, channel));
	if (msg.params.size() < 2)
		return (RPL_CHANNELMODEIS(client, channel));
	// if (!channel->hasMode(CH_MODE_OPERATOR, client))
	// 	return (ERR_CHANOPRIVSNEEDED(client, channel));
	std::string	modes = msg.params[1];
	size_t			nextParam = 1;
	std::string	reply;
	char		op = '*';

	for (size_t i = 0; i < modes.length(); i++)
	{
		if (modes[i] == '+' || modes[i] == '-') {
			op = modes[i];
			continue;
		}
		if (op == '+' || op == '-') {
			reply = applyMode(channel, client, modes[i], op, ((msg.params.size() > ++nextParam) ? msg.params[nextParam] : ""));
			if (reply != NO_REPLY())
				client->write(reply);
		}
		op = '*';
	}
	return (NO_REPLY());
}
