#include "replies.hpp"
#include "commands.hpp"
#include "validation.hpp"
#include "Channel.hpp"
#include "utils.hpp"
#include <iostream>

// std::string	DCCMSG(Message msg, Server *server, Client *client)
// {

// }

std::string	isDCC(std::string param)
{
	// std::string message;
	Message msg = parseMessage(param);


	// std::cout << msg.cmd << " " << msg.params.size() << std::endl;

	if (msg.cmd == std::string("\x01") + "DCC" && msg.params.size() == 5)
	{
		return (param);
	}
	return ("");
}

std::string	PRIVMSG(Message msg, Server *server, Client *client) {
	std::vector<std::string>	tokens;
	Client						*c_target;
	Channel						*cnl_target;
	std::string					ddc;

	if (msg.params.size() < 2)
		return(ERR_NEEDMOREPARAMS(client, msg.cmd));
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
					client->write(ERR_CANNOTSENDTOCHAN(client, cnl_target));
				else
				{
					if (!msg.params[1].empty())
						cnl_target->broadcast(MSG_PRIVMSG(client, cnl_target, msg.params[1]), client);
					else
						client->write(ERR_NOTEXTTOSEND(client));
				}
			}
			else
			{
				c_target = server->getClient(tokens[i]);
				if (c_target && c_target != client)
				{
					ddc = isDCC(msg.params[1]);
					// std::cout << ddc + "aa" << std::endl;
					if (ddc.length() != 0)
					{
						c_target->write(MSG_PRIVMSG(client, c_target, ddc));
						return (NO_REPLY());
					}
					c_target->write(MSG_PRIVMSG(client, c_target, msg.params[1]));
				}
				else
					client->write(ERR_NORECIPIENT(client, msg.cmd));
			}
		}
		else
			client->write(ERR_NORECIPIENT(client, msg.cmd));
	}
	return (NO_REPLY());
}