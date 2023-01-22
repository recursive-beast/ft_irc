/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-oma <aait-oma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:12:56 by mmessaou          #+#    #+#             */
/*   Updated: 2023/01/22 15:52:22 by aait-oma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "utils.hpp"
#include <iostream>

void	_PASS(std::string line, Server *server, Client *client)
{
	std::vector<std::string>	tokens;

	tokens = split(line, " ");
	if (client->registred)
		client->write(":Unauthorized command (already registered)\n");
	else if (tokens.size() > 1)
		client->pass = tokens[1];
	else
		client->write("PASS :Not enough parameters\n");
	(void)server;
}

void	_NICK(std::string line, Server *server, Client *client)
{
	std::vector<std::string>	tokens;

	tokens = split(line, " ");
	if (client->pass.size() == 0 || client->pass != server->password)
	{
		client->write(":Password Incorrect\n");
		client->disconnect();
	}
	else if (tokens.size() < 1)
		client->write("NICK :Not enough parameters\n");
	else if (!checkNickName(tokens[1]))
		client->write(":Erroneous Nickname\n");
	else if (server->setClientNickname(client, tokens[1]))
		client->write(":Nickname is already in use.\n");
	else
		client->write(":Welcome to the *LMA9AWID* Internet Relay Chat Network " + tokens[1] + "\n");
	_Registred(client);
}

void	_USER(std::string line, Server *server, Client *client)
{
	std::vector<std::string>	tokens;
	size_t 						pos;

	tokens = split(line, " ");
	if (client->registred)
		client->write(":Unauthorized command (already registered)\n");
	else if (client->pass.size() == 0 || client->pass != server->password)
	{
		client->write(":Password Incorrect\n");
		client->disconnect();
	}
	else if (tokens.size() < 5)
		client->write("USER :Not enough parameters\n");
	else if (tokens[2].size() > 1 && !isdigit(tokens[2][0]))
		client->write("USER :Unknown MODE flag\n");
	else
	{
		pos = line.rfind(":");
		if (pos != std::string::npos)
			client->realName = line.substr(pos + 1);
		client->userName = tokens[1];
		client->mood = std::stoi(tokens[2]);
	}
	_Registred(client);
}

//aait-oma
//{

void    _JOIN(std::string line, Server *server, Client *client)
{
    std::vector<std::string>    tokens;
    std::string                 _channel;

    tokens = split(line, ",");
    if (tokens.size() != 0)
    {
        if (tokens[0] == "0")
        {
            
        }
        else
        {
            for (size_t i = 0; i < tokens.size(); i++)
            {
                _channel = skipLeadingWhitespaces(tokens[i]);
                if (startsWithHash(_channel))
                {
                    if (server->channelExists(_channel))
                    {
                        // server->addUserToChannel(_channel, client);
                        client->write(client->nickname + " JOIN " + _channel);
                    }
                    else
                    {
                        
                    }
                }
            }
        }
    }
	(void) server;
	(void) client;
}

//}

std::map<std::string, Parser::func>	Parser::commandes;

void	Parser::initCmnds()
{
	Parser::commandes["PASS"] = _PASS;
	Parser::commandes["NICK"] = _NICK;
	Parser::commandes["USER"] = _USER;

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
		it->second(line, server, client);
	else
	{
		std::cout << "000" << std::endl;
	}
}