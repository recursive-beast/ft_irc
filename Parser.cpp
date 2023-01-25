/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmessaou <mmessaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:12:56 by mmessaou          #+#    #+#             */
/*   Updated: 2023/01/25 11:24:48 by mmessaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/Commandes.hpp"
#include "utils.hpp"
#include <iostream>

//aait-oma
#pragma region
//{
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
				it = server->getMapElement(_channels[i]);
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

//}
#pragma endregion

std::map<std::string, Parser::func>	Parser::commandes;

void	Parser::initCmnds()
{
	Parser::commandes["PASS"] = _PASS;
	Parser::commandes["NICK"] = _NICK;
	Parser::commandes["USER"] = _USER;

	Parser::commandes["PRIVMSG"] = _PRIVMSG;
	//aait-oma
	Parser::commandes["JOIN"] = _JOIN;

}

void	Parser::parseLine(std::string line, Server *server, Client *client)
{
	std::string	cmd;
	std::map<std::string, Parser::func>::iterator	it;

	cmd = line.substr(0, line.find(" "));
	it = commandes.find(cmd);
	if (it != commandes.end())
	{
		if (!client->registred && cmd != "PASS" && cmd != "NICK" && cmd != "USER")
			client->write(hostname + " 451 " + ":You have not registered\n");
		else
			it->second(line, server, client);
	}
	else
		client->write(hostname + " 421 " + cmd + " :Unknown command\n");
}
