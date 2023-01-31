/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pars_utils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-oma <aait-oma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:31:50 by mmessaou          #+#    #+#             */
/*   Updated: 2023/01/31 14:48:52 by aait-oma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include <string>

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
bool startsWith(const std::string &str, char c)
{
    return str.front() == c;
}

std::string skipLeadingWhitespaces(const std::string &str)
{
    size_t firstNonSpace = str.find_first_not_of(" \t\n\r\f\v");
    if (firstNonSpace != std::string::npos)
        return str.substr(firstNonSpace);
    return str;
}

void changeString(std::string& str)
{
    if (!str.empty() && str[0] == '&')
        str[0] = '#';
}

bool	isValidChanstring(const std::string &s)
{
	for (size_t i = 0; i < s.size(); i++)
		if (s[i] == '\0' || s[i] == '\a' || s[i] == '\r' || s[i] == '\n' || s[i] == ' ' || s[i] == ',' || s[i] == ':')
			return false;
	return true;
}

bool	isValidChannelid(const std::string &s) {
	if (s.size() != 5)
		return false;
	for (size_t i = 0; i < s.size(); i++)
		if (!isdigit(s[i]) && (s[i] < 'A' || s[i] > 'Z'))
			return false;
	return true;
}

bool	isValidChannel(const std::string &s) 
{
	if (s.empty())
		return false;
	if (s[0] == '#' || s[0] == '+')
		return isValidChanstring(s.substr(1));
	if (s[0] == '&')
		return isValidChanstring(s.substr(1));
	if (s[0] == '!')
	{
		size_t pos = s.find(":");
		if (pos == std::string::npos)
			return isValidChannelid(s.substr(1)) && isValidChanstring(s.substr(6));
		else
			return isValidChannelid(s.substr(1, pos - 1)) && isValidChanstring(s.substr(pos + 1));
	}
	return false;
}
