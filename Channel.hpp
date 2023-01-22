/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-oma <aait-oma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 10:08:05 by aait-oma          #+#    #+#             */
/*   Updated: 2023/01/22 13:50:13 by aait-oma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Client.hpp"
# include <string>
# include <map>
# include <poll.h>
# include <vector>
# include <set>

class Channel
{
private:
    std::string         channelName;
    std::string         password;
    std::string         topic;
    std::set<Client *>  members;
    std::set<Client *>  operators;
public:
    Channel();
    Channel(const Channel& other);
    Channel& operator=(const Channel &other);
    ~Channel();
    // Getters
    std::string getChannelName() const;
    std::string getTopic() const;
    std::string getPassword() const;
    std::set<Client *> getMembers() const;
    std::set<Client *> getOperators() const;
    std::set<Client *> getBanned() const;
    
    void join(Client *client);
    void leave(Client *client);
    void sendMessage(Client *sender, const std::string &message);
    void setTopic(const std::string &topic);
    void addOperator(Client *operat);
    void removeOperator(Client *operat);
    void kick(Client *user);
    void ban(Client *user);
};

#endif