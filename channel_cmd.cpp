/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_cmd.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-oma <aait-oma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:59:40 by aait-oma          #+#    #+#             */
/*   Updated: 2023/01/21 18:55:56 by aait-oma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"
#include "utils.hpp"
#include <vector>

bool Server::channelExists(std::string channel)
{
    if (channels.find(channel) != channels.end())
        return true;
    return false;
}

void    Server::addUserToChannel(std::string channel, Client *client)
{
    channels[channel].push_back(client);
}

void    Server::broadcastMessageToChannel(std::string channel, std::string message)
{
    
}

bool startsWithHash(const std::string &str)
{
    return str.front() == '#';
}

std::string skipLeadingWhitespaces(const std::string &str)
{
    size_t firstNonSpace = str.find_first_not_of(" \t\n\r\f\v");
    if (firstNonSpace != std::string::npos)
        return str.substr(firstNonSpace);
    return str;
}

void    _JOIN(std::string line, Client *client, Server *server)
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
                        server->addUserToChannel(_channel, client);
                        client->write(client->nickname + " JOIN " + _channel);
                        
                    }
                    else
                    {
                        
                    }
                }
            }
        }
    }
}