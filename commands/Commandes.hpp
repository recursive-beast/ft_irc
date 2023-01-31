/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commandes.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-oma <aait-oma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:43:14 by mmessaou          #+#    #+#             */
/*   Updated: 2023/01/31 14:07:10 by aait-oma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDES_HPP
# define COMMANDES_HPP
# include "../Parser.hpp"
# include <iostream>

void	_PASS(std::string line, Server *server, Client *client);
void	_NICK(std::string line, Server *server, Client *client);
void	_USER(std::string line, Server *server, Client *client);

void	_PRIVMSG(std::string line, Server *server, Client *client);

//ChannelOperations.cpp
void    _JOIN(std::string line, Server *server, Client *client);
void    _PART(std::string line, Server *server, Client *client);
void	_KICK(std::string line, Server *server, Client *client);
void    _TOPIC(std::string line, Server *server, Client *client);
#endif
