/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmessaou <mmessaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:24:29 by mmessaou          #+#    #+#             */
/*   Updated: 2023/01/26 15:06:39 by mmessaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Parser.hpp"
#include "../utils.hpp"
#include <iostream>

void	_MODE(std::string line, Server *server, Client *client)
{
	std::vector<std::string>					tokens;
	std::map<std::string, Channel>::iterator	chnl_it;
	std::set<Client *>  						_members;
	std::set<Client *>::iterator  				clt_it;

	tokens = split(line, " ");
	if (tokens.size() > 2)
	{
		if (tokens[1][0] == '#' && server->channelExists(tokens[1]))
		{
			// chanel mood
		}
		else
		{
			if (tokens[1] == client->nickname)
			{

			}
		}
	}
}
