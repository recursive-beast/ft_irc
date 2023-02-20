/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commandes.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmessaou <mmessaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:43:14 by mmessaou          #+#    #+#             */
/*   Updated: 2023/02/20 14:14:59 by mmessaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDES_HPP
# define COMMANDES_HPP
# include "../Parser.hpp"
# include <iostream>

// ConnectionRegistration.cpp
void	_PASS(std::string line, Server *server, Client *client);
void	_NICK(std::string line, Server *server, Client *client);
void	_USER(std::string line, Server *server, Client *client);

// Messages.cpp
void	_PRIVMSG(std::string line, Server *server, Client *client);

//ChannelOperations.cpp
void    _JOIN(std::string line, Server *server, Client *client);
void    _PART(std::string line, Server *server, Client *client);
void	_KICK(std::string line, Server *server, Client *client);
void    _TOPIC(std::string line, Server *server, Client *client);
void	_Notice(std::string line, Server *server, Client *client);

// Mode.cpp
void	_MODE(std::string line, Server *server, Client *client);

#endif
