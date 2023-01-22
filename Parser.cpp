/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmessaou <mmessaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:12:56 by mmessaou          #+#    #+#             */
/*   Updated: 2023/01/22 16:35:12 by mmessaou         ###   ########.fr       */
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
		client->write(hostname + " 462 " + client->nickname
			+ " :Unauthorized command (already registered)\n");
	else if (tokens.size() > 1)
		client->pass = tokens[1];
	else
		client->write(hostname + " 461 " + "PASS :Not enough parameters\n");
	(void)server;
}

void	_NICK(std::string line, Server *server, Client *client)
{
	std::vector<std::string>	tokens;
	bool						rgstr;

	tokens = split(line, " ");
	if (client->registred)
		rgstr = true;
	if (tokens.size() < 2)
		client->write(hostname + " 461 " + "NICK :Not enough parameters\n");
	else if (client->pass.size() == 0 || client->pass != server->password)
	{
		client->write(hostname + " 464 " + tokens[1] + " :Password Incorrect\n");
		client->disconnect();
	}
	else if (!checkNickName(tokens[1]))
		client->write(hostname + " 432 " + client->nickname + " :Erroneous Nickname\n");
	else if (server->setClientNickname(client, tokens[1]))
		client->write(hostname + " 433 " + client->nickname + " :Nickname is already in use.\n");
	else if (!rgstr && client->registred)
		client->write(hostname + " 001 " + client->nickname
			+ " :Welcome to the *LMA9AWID* Internet Relay Chat Network " + client->nickname + "\n");
	_Registred(client);
}

void	_USER(std::string line, Server *server, Client *client)
{
	std::vector<std::string>	tokens;
	size_t 						pos;

	tokens = split(line, " ");
	if (client->registred)
		client->write(hostname + " 462 " + client->nickname
			+ " :Unauthorized command (already registered)\n");
	else if (client->pass.size() == 0 || client->pass != server->password)
	{
		client->write(hostname + " 464 " + client->nickname + " :Password Incorrect\n");
		client->disconnect();
	}
	else if (tokens.size() < 5)
		client->write(hostname + " 461 " + "USER :Not enough parameters\n");
	else if (tokens[2].size() > 1 && !isdigit(tokens[2][0]))
		client->write(hostname + " 501 " + ": Unknown MODE flag\n");
	else
	{
		pos = line.rfind(":");
		if (pos != std::string::npos)
			client->realName = line.substr(pos + 1);
		else
			client->disconnect();
		client->userName = tokens[1];
		client->mood = std::stoi(tokens[2]);
	}
	_Registred(client);
	if (client->registred)
		client->write(hostname + " 001 " + client->nickname
			+ " :Welcome to the * MSA * Internet Relay Chat Network " + client->nickname + "\n");
}

void	_PRIVMSG(std::string line, Server *server, Client *client)
{
	std::vector<std::string>	tokens;
	Client						*c_target;

	tokens = split(line, " ");
	if (tokens.size() > 2)
	{
		c_target = server->getClient(tokens[1]);
		if (c_target)
		{
			c_target->write(":" + client->nickname + " PRIVMSG " + c_target->nickname
				+ " :" + skipWords(line, 2) );
		}
	}
	else
		client->write(hostname + " 411 " + ":No recipient given (PRIVMSG)\n");
}

//aait-oma
#pragma region
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
#pragma endregion

std::map<std::string, Parser::func>	Parser::commandes;

void	Parser::initCmnds()
{
	Parser::commandes["PASS"] = _PASS;
	Parser::commandes["NICK"] = _NICK;
	Parser::commandes["USER"] = _USER;

	//aait-oma
	Parser::commandes["JOIN"] = _JOIN;

	Parser::commandes["PRIVMSG"] = _PRIVMSG;
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
		client->write(hostname + " 421 " + cmd + " :Unknown command\n");
}