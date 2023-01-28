/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-oma <aait-oma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:50:25 by aait-oma          #+#    #+#             */
/*   Updated: 2023/01/28 21:09:04 by aait-oma         ###   ########.fr       */
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

void    Channel::part(Client *client)
{
    if (client)
        members.erase(client);
}

void    Channel::kick(std::string nickname)
{
    std::set<Client *>::iterator it;
    if (isOperator(nickname))
    {
        it = operators.begin();
		for (; it != operators.end(); it++)
		{
			if ((*it)->nickname == nickname)
            {
                removeOperator(*it);
                break;
            }
		}
    }
    it = members.begin();
    for (; it != operators.end(); it++)
    {
        if ((*it)->nickname == nickname)
        {
            part(*it);
            break;
        }
    }
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

 bool Channel::isEmpty(void)
{
    if (members.empty())
        return true;
    return false;
}

bool	Channel::isMember(std::string nickname)
{
    std::set<Client *>::iterator it = members.begin();
    for (; it != members.end(); it++)
    {
        if ((*it)->nickname == nickname)
            return true;
    }
    return false;
}
bool	Channel::isOperator(Client *client)
{
    return operators.find(client) != operators.end();
}
bool	Channel::isOperator(std::string nickname)
{
    std::set<Client *>::iterator it = operators.begin();
    for (; it != operators.end(); it++)
    {
        if ((*it)->nickname == nickname)
            return true;
    }
    return false;
}