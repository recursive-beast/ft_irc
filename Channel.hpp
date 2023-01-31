/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-oma <aait-oma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 10:08:05 by aait-oma          #+#    #+#             */
/*   Updated: 2023/01/28 21:09:27 by aait-oma         ###   ########.fr       */
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
	std::set<std::string>  banned;
	std::set<Client *>  operators;
public:
	Channel();
	Channel(std::string _channelName, Client * c, std::string _password = "");
	Channel(const Channel& other);
	Channel& operator=(const Channel &other);
	~Channel();
	// Getters
	std::string	getChannelName() const;
	std::string	getTopic() const;
	std::string	getPassword() const;
	std::set<Client *>	getMembers() const;
	std::set<Client *>	getOperators() const;
	void	join(Client *client);
	void	part(Client *client);
	void	setTopic(const std::string &topic_);
	void	addOperator(Client *operat);
	void	removeOperator(Client *operat);
	void    kick(std::string nickname);
	void	ban(std::string nickname);
	bool	alreadyExists(Client * client);
	bool	alreadyBanned(std::string nickname);
	bool	islocked(void);
	bool	isEmpty(void);
	bool	isMember(std::string nickname);
	bool	isOperator(Client *client);
	bool	isOperator(std::string nickname);
};

#endif