#include "replies.hpp"
#include "commands.hpp"
#include "validation.hpp"
#include "Channel.hpp"
#include "utils.hpp"

std::string	NOTICE(Message msg, Server *server, Client *client) {
	std::vector<std::string>	tokens;
	Client						*c_target;
	Channel						*cnl_target;

	if (msg.params.size() < 2)
		return(NO_REPLY());
	tokens = split(msg.params[0], ",");
	for (size_t i = 0; i < tokens.size(); i++)
	{
		if (!tokens[i].empty())
		{
			cnl_target = server->getChannel(tokens[i]);
			if (cnl_target)
			{
				if ((cnl_target->hasMode('n') && !cnl_target->isOn(client))
					|| (cnl_target->hasMode('m') && !(cnl_target->hasMode('v', client)
					|| cnl_target->hasMode('o', client))))
					client->write(NO_REPLY());
				else if (!msg.params[1].empty())
						cnl_target->broadcast(MSG_PRIVMSG(client, cnl_target, msg.params[1]), client);
			}
			else
			{
				c_target = server->getClient(tokens[i]);
				if (c_target && c_target != client)
					c_target->write(MSG_PRIVMSG(client, c_target, msg.params[1]));
			}
		}
	}
	return (NO_REPLY());
}