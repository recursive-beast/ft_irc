#include "replies.hpp"
#include "commands.hpp"
#include "validation.hpp"
#include "Channel.hpp"
#include <string>

bool	addMode(Channel *channel, Client *client, char mode, bool isOp, std::string parms) {
	bool	modeApplyed = false;

	switch (mode)
	{
		case CH_MODE_INVITE_ONLY:
			return (channel->setMode(mode));
			break;
		case CH_MODE_MODERATED:
			return (channel->setMode(mode));
			break;
		case CH_MODE_NO_OUTSIDE:
			return (channel->setMode(mode));
			break;
		case CH_MODE_TOPIC:
			if (isOp) {
				channel->topic = parms;
				return (channel->setMode(mode));
			}
			break;
		case CH_MODE_KEY:
			if (isOp) {
				channel->key = parms;
				return (channel->setMode(mode));
			}
			break;
		case CH_MODE_LIMIT:
			if (isOp) {
				channel->limit = std::stoi(parms);
				return (channel->setMode(mode));
			}
			break;
		case CH_MODE_CREATOR:
			return (channel->setMode(mode));
			break;
		case CH_MODE_OPERATOR:
			return (channel->setMode(mode));
			break;
		case CH_MODE_VOICE:
			if (isOp)
				return (channel->setMode(mode, client));
			break;
		default:
			return(false);
			break;
	}
}

void TraverseModes(std::string &str, int N)
{
	// std::string::iterator	it = str.begin();
	std::size_t				found;

	for (int i = 0; i < N; i++)
	{
		found = str.find_first_not_of("+-");
		// if ()
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

	}
}

