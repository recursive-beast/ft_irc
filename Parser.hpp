/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-oma <aait-oma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:10:55 by mmessaou          #+#    #+#             */
/*   Updated: 2023/01/30 13:34:37 by aait-oma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define hostname (std::string(":msa057@localhost"))

# include "Server.hpp"

class Parser {
	public:
		typedef	void (*func)(std::string line, Server *server, Client *client);
		static void	parseLine(std::string line, Server *server, Client *client);
		static void	initCmnds();
		static std::map<std::string, func>	commandes;

	private:

};

bool		checkNickName(std::string nickName);
void		_Registred(Client *client);
std::string	skipWords(std::string line, int nbr);
//aait-oma part
std::string skipLeadingWhitespaces(const std::string &str);
bool		startsWith(const std::string &str, char c);
void 		changeString(std::string& str);
bool		isValidChannel(const std::string &s);
#endif /* PARSER_H */
