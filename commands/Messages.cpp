/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Messages.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-oma <aait-oma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:17:18 by mmessaou          #+#    #+#             */
/*   Updated: 2023/01/27 14:39:27 by aait-oma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Parser.hpp"
#include "../utils.hpp"
#include <iostream>

void	_PRIVMSG(std::string line, Server *server, Client *client)
{
	std::vector<std::string>					tokens;
	Client										*c_target;
	std::map<std::string, Channel>::iterator	chnl_it;
	std::set<Client *>  						_members;
	std::set<Client *>::iterator  				clt_it;

	tokens = split(line, " ");
	if (tokens.size() > 2)
	{
		if ((tokens[1][0] == '#' || tokens[1][0] == '&') && server->channelExists(tokens[1]))
		{
			chnl_it = server->getChannel(tokens[1]);
			_members = chnl_it->second.getMembers();
			if (chnl_it->second.alreadyExists(client) && !chnl_it->second.alreadyBanned(client->nickname))
			{
				clt_it = _members.begin();
				while (clt_it != _members.end())
				{
					if ((*clt_it) != client)
						(*clt_it)->write(":" + client->nickname + " PRIVMSG " + (*clt_it)->nickname
							+ " :" + skipWords(line, 2) + "\n");
					clt_it++;
				}
			}
			else
				client->write(hostname + " 404 " + tokens[1] + ":Cannot send to channel\n");
		}
		else
		{
			c_target = server->getClient(tokens[1]);
			if (c_target && c_target != client)
			{
				c_target->write(":" + client->nickname + " PRIVMSG " + c_target->nickname
					+ " :" + skipWords(line, 2) + "\n");
			}
		}
	}
	else
		client->write(hostname + " 411 " + ":No recipient given (PRIVMSG)\n");
}
