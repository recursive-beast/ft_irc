/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandes.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmessaou <mmessaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:43:14 by mmessaou          #+#    #+#             */
/*   Updated: 2023/01/24 10:14:38 by mmessaou         ###   ########.fr       */
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
#endif
