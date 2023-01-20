/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pars_utils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmessaou <mmessaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:31:50 by mmessaou          #+#    #+#             */
/*   Updated: 2023/01/20 18:23:01 by mmessaou         ###   ########.fr       */
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
