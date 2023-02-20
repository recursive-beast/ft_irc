#include "replies.hpp"
#include "commands.hpp"
#include "validation.hpp"
#include "Channel.hpp"
#include "utils.hpp"

static std::string	forEach(
	Server *server,
	Client *client,
	std::string chname,
	std::string key
) {
	Channel	*channel;

	channel = server->getChannel(chname);
	if (!channel) {
		if (!ischannel(chname))
			return (ERR_BADCHANMASK(client, chname));
		channel = server->createChannel(chname, client);
		channel->setMode(CH_MODE_TOPIC);
		channel->setMode(CH_MODE_NO_OUTSIDE);
		if (!key.empty()) {
			channel->setMode(CH_MODE_KEY);
			channel->key = key;
		}
	}
	if (channel->hasMode(CH_MODE_INVITE_ONLY) && !channel->isInvited(client))
		return (ERR_INVITEONLYCHAN(client, channel));
	if (channel->hasMode(CH_MODE_LIMIT) && channel->getCount() + 1 > channel->limit)
		return (ERR_CHANNELISFULL(client, channel));
	if (channel->hasMode(CH_MODE_KEY) && channel->key != key)
		return (ERR_BADCHANNELKEY(client, channel));
	channel->join(client);
	channel->broadcast(MSG_JOIN(client, channel));
	client->write(MSG_MODE(client, channel));
	client->write(RPL_TOPIC(client, channel));
	client->write(RPL_NAMREPLY(client, channel));
	return (RPL_ENDOFNAMES(client, channel));
}

std::string	JOIN(Message msg, Server *server, Client *client) {
	Message						partMsg;
	std::vector<std::string>	chnames;
	std::vector<std::string>	keys;
	std::string					reply;
	size_t						chname_empty_count = 0;

	if (!client->registered)
		return (ERR_NOTREGISTERED(client, msg.cmd));
	if (msg.params.size() == 1 && msg.params[0] == "0") {
		partMsg.cmd = "PART";
		partMsg.params.push_back(join(server->getChannelNames(client), ","));
		Dispatcher::dispatch(partMsg, server, client);
		return (NO_REPLY());
	}
	if (msg.params.size() < 1)
		return (ERR_NEEDMOREPARAMS(client, msg.cmd));
	chnames = split(msg.params[0], ",");
	if (msg.params.size() > 1)
		keys = split(msg.params[1], ",");
	for (size_t i = 0; i < chnames.size(); i++) {
		if (chnames[i].empty()) {
			if (++chname_empty_count == chnames.size())
				return (ERR_NEEDMOREPARAMS(client, msg.cmd));
			continue;
		}
		if (i < keys.size())
			reply = forEach(server, client, chnames[i], keys[i]);
		else
			reply = forEach(server, client, chnames[i], "");
		if (reply != NO_REPLY())
			client->write(reply);
	}
	return (NO_REPLY());
}
