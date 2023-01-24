/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-oma <aait-oma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:50:25 by aait-oma          #+#    #+#             */
/*   Updated: 2023/01/24 16:01:39 by aait-oma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel() {}
Channel::Channel(std::string _channelName, Client *c, std::string _password) 
    : channelName(_channelName)
    , password(_password) 
{
    this->members.insert(c);
    addOperator(c);
}

Channel::Channel(const Channel& other) : channelName(other.channelName), password(other.password), topic(other.topic),
    members(other.members), operators(other.operators) {}

Channel& Channel::operator=(const Channel &other)
{
    if (this != &other) 
    {
        channelName = other.channelName;
        password = other.password;
        members = other.members;
        topic = other.topic;
        operators = other.operators;
    }
    return *this;
}

Channel::~Channel() {}

std::string Channel::getChannelName() const { return this->channelName; }
std::string Channel::getTopic() const { return this->topic; }
std::string Channel::getPassword() const { return this->password; }
std::set<Client *> Channel::getMembers() const { return this->members; }
std::set<Client *> Channel::getOperators() const { return this->operators; }

void    Channel::join(Client *client)
{
    if (client)
        members.insert(client);
}

void    Channel::kick(Client *client)
{
    if (client)
        members.erase(client);
}

void    Channel::setTopic(const std::string &topic_) { topic = topic_; }

void    Channel::addOperator(Client *operat)
{
    if (operat)
        operators.insert(operat);
}
void    Channel::removeOperator(Client *operat)
{
    if (operat)
        operators.erase(operat);
}

bool    Channel::alreadyExists(Client * client)
{
    return members.find(client) != members.end();
}
void    Channel::ban(std::string nickname)
{
    banned.insert(nickname);
}
bool    Channel::alreadyBanned(std::string nickname)
{
    return banned.find(nickname) != banned.end();
}

bool    Channel::islocked(void)
{
    return password != "" ;
}