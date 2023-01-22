/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pars_utils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <syakoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:31:50 by mmessaou          #+#    #+#             */
/*   Updated: 2023/01/22 17:11:54 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

#define LETTERS	(std::string("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"))
#define DIGITS	(std::string("0123456789"))
#define SPECIAL	(std::string("[]\\`_^{}|"))

bool	checkNickName(std::string nickName)
{
	if (nickName.size() == 0 || nickName.size() > 9 || (LETTERS + SPECIAL).find(nickName[0]) == std::string::npos)
		return (false);
	nickName.erase(0, 1);
	while (nickName.size()) {
		if ((LETTERS + SPECIAL + DIGITS + "-").find(nickName[0]) == std::string::npos)
			break ;
		nickName.erase(0, 1);
	}
	return (nickName.size() == 0);
}

void	_Registred(Client *client)
{
	if (client->nickname.size() && client->userName.size() && client->realName.size())
		client->registred = true;
}

std::string	skipWords(std::string line, int nbr)
{
	line = line.substr(line.find_first_not_of(' '));
	for (int i = 0; i < nbr; i++)
	{
		line = line.substr(line.find_first_of(' '));
		line = line.substr(line.find_first_not_of(' '));
	}
	return (line);
}


// aait-oma
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
