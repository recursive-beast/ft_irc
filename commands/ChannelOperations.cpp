/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelOperations.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-oma <aait-oma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:45:21 by aait-oma          #+#    #+#             */
/*   Updated: 2023/01/28 21:29:01 by aait-oma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Parser.hpp"
#include "../utils.hpp"
#include <iostream>

void	leaveAll(Server *server, Client *client)
{
	std::map<std::string, Channel> map = server->getChannels();
	std::map<std::string, Channel>::iterator it1 = map.begin();
	for (; it1 != map.end(); it1++)
	{
		if (it1->second.alreadyExists(client))
		{
			it1->second.part(client);
			client->write(client->nickname + " PART " + it1->second.getChannelName() + "\n");
			if (it1->second.isEmpty())
				server->deleteChannel(it1->first);
		}
	}
}

void    _JOIN(std::string line, Server *server, Client *client)
{
    std::vector<std::string>    tokens;
	std::map<std::string, Channel>::iterator	it;
	std::vector<std::string>	_keys;
	std::vector<std::string>	_channels;

    tokens = split(line, " ");
    if (tokens.size() == 1)
		client->write("ERR_NEEDMOREPARAMS\n");
	else if (tokens.size() <= 3)
    {
		_channels = tokens.size() > 1 ? split(tokens[1], ",") : std::vector<std::string>();
		_keys = tokens.size() > 2 ? split(tokens[2], ",") : std::vector<std::string>();
		if (tokens.size() == 2 && _channels[0] == "0")
		{
			leaveAll(server, client);
			return ;
		}
		for (size_t i = 0; i < _channels.size();i++)
		{
			if (startsWith(_channels[i], '#') || startsWith(_channels[i], '&'))
			{
				if (startsWith(_channels[i], '&'))
					changeString(_channels[i]);
				if (!server->channelExists(_channels[i]))
				{
					server->createChannel(_channels[i], Channel(_channels[i], client, i < _keys.size() ? _keys[i] : ""));
					client->write(client->nickname + " JOIN " + _channels[i] + "\n");
					continue ;
				}
				it = server->getChannel(_channels[i]);
				if (it->second.alreadyBanned(client->nickname))
					client->write("ERR_BANNEDFROMCHAN\n");
				else if (it->second.alreadyExists(client))
					client->write("error! alreadyExists\n");
				if (it->second.islocked())
				{
					if (i < _keys.size() && it->second.getPassword() == _keys[i])
					{
						it->second.join(client);
						client->write(client->nickname + " JOIN " + _channels[i] + "\n");
					}
					else
						client->write("ERR_BADCHANNELKEY\n");
				}
				else {
					if (i < _keys.size() && _keys[i] != "")
						client->write("ERR_BADCHANNELKEY\n");
					else{
						it->second.join(client);
						client->write(client->nickname + " JOIN " + _channels[i] + "\n");
					}
				}
			}
		}
	}
	else
		client->write("error! too much parameter");
}

void    _PART(std::string line, Server *server, Client *client)
{
    std::vector<std::string>                    tokens = split(line, " ");
    std::map<std::string, Channel>::iterator	it;
	std::vector<std::string>	                _channels;

    if (tokens.size() == 1)
		client->write("ERR_NEEDMOREPARAMS\n");
    else if (tokens.size() == 2)
    {
        _channels = tokens.size() > 1 ? split(tokens[1], ",") : std::vector<std::string>();
		if (_channels[0] == "0")
		{
			leaveAll(server, client);
			return ;
		}
		for (size_t i = 0; i < _channels.size();i++)
		{
			if (startsWith(_channels[i], '#') || startsWith(_channels[i], '&'))
			{
				if (startsWith(_channels[i], '&'))
					changeString(_channels[i]);
				if (server->channelExists(_channels[i]))
				{
                    it = server->getChannel(_channels[i]);
                    if (it->second.alreadyExists(client))
                    {
                        it->second.part(client);
                        client->write(client->nickname + " PART " + _channels[i] + "\n");
                    }
                    else
                        client->write("ERR_NOTONCHANNEL\n");
				}
                else
                    client->write(_channels[i] + " :No such channel\n");
			}
		}
    }
}

void	_KICK(std::string line, Server *server, Client *client)
{
	std::vector<std::string>    tokens;
	std::map<std::string, Channel>::iterator	it;
	std::vector<std::string>	_clients;
	std::vector<std::string>	_channels;
	std::string	_comment;

    tokens = split(line, " ");
    if (tokens.size() == 1)
		client->write("ERR_NEEDMOREPARAMS\n");
	else
	{
		_channels = tokens.size() > 1 ? split(tokens[1], ",") : std::vector<std::string>();
		_channels = tokens.size() > 2 ? split(tokens[2], ",") : std::vector<std::string>();
		_comment = tokens.size() > 3 ? tokens[3] : "";
		for (size_t i = 0; i < _channels.size(); i++)
		{
			if (startsWith(_channels[i], '#') || startsWith(_channels[i], '&'))
			{
				if (startsWith(_channels[i], '&'))
					changeString(_channels[i]);
				if (server->channelExists(_channels[i]))
				{
					it = server->getChannel(_channels[i]);
					if (!it->second.isOperator(client))
					{
						for (size_t j = 0; j < _clients.size(); j++)
						{
							if (it->second.isMember(_clients[j])){
								it->second.kick(_clients[j]);
								client->write("KICK " + _channels[i] + " " + _clients[j] + " :" + client->nickname);
								tokens.size() == 4 ? client->write(" :" + _comment + "\n") : client->write("\n");
							}
							else
								client->write(":No such nick/channel\n");
						}
					}
				}
				else
					client->write(":No such nick/channel\n");
			}
			else
				client->write(":No such nick/channel\n");
		}
	}
}

// void    _TOPIC(std::string line, Server *server, Client *client)
// {
    
// }