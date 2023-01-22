/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-oma <aait-oma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:50:25 by aait-oma          #+#    #+#             */
/*   Updated: 2023/01/22 13:50:36 by aait-oma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel() {}

Channel::Channel(const Channel& other) : channelName(other.channelName), password(other.password), topic(other.topic),
    members(other.members), operators(other.operators) {}

Channel& Channel::operator=(const Channel &other)
{
    if (this != &other) 
    {
        channelName = other.channelName;
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

// void    Channel::join(Client *client)
// {
    
// }