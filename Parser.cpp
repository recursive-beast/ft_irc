/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-oma <aait-oma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:12:56 by mmessaou          #+#    #+#             */
/*   Updated: 2023/01/27 17:29:08 by aait-oma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/Commandes.hpp"
#include "utils.hpp"
#include <iostream>

std::map<std::string, Parser::func>	Parser::commandes;

void	Parser::initCmnds()
{
	Parser::commandes["PASS"] = _PASS;
	Parser::commandes["NICK"] = _NICK;
	Parser::commandes["USER"] = _USER;

	Parser::commandes["PRIVMSG"] = _PRIVMSG;
	//aait-oma
	Parser::commandes["JOIN"] = _JOIN;
	Parser::commandes["PART"] = _PART;
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
