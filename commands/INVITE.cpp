#include "replies.hpp"
#include "commands.hpp"
#include "validation.hpp"
#include "Channel.hpp"

std::string	INVITE(Message msg, Server *server, Client *client) {
	Channel	*channel;
	Client	*invited;

	if (!client->registered)
		return (ERR_NOTREGISTERED(client, msg.cmd));
	if (msg.params.size() < 2)
		return (ERR_NEEDMOREPARAMS(client, msg.cmd));
	invited = server->getClient(msg.params[0]);
	if (!invited)
		return (ERR_NOSUCHNICK(client, msg.params[0]));
	channel = server->getChannel(msg.params[0]);
	if (channel) {
		if (!channel->isOn(client))
			return (ERR_NOTONCHANNEL(client, channel));
		if (channel->hasMode(CH_MODE_INVITE_ONLY) && !channel->hasMode(CH_MODE_OPERATOR, client))
			return (ERR_CHANOPRIVSNEEDED(client, channel));
		if (channel->isOn(invited))
			return (ERR_USERONCHANNEL(client, invited, channel));
		channel->invite(invited);
	}
	invited->write(MSG_INVITE(client, invited, channel));
	return (RPL_INVITING(client, invited, channel));
}
