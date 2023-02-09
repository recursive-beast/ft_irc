#ifndef REPLIES_HPP
# define REPLIES_HPP

# include "Client.hpp"
# include <string>

std::string	NO_REPLY();
// :<sender> <reply code> <receiver> <message>\r\n
std::string	REPLY(std::string reply_code, Client *client, std::string message);
std::string	BROADCAST_REPLY(std::string reply_code, std::string message);
std::string	ERR_ALREADYREGISTRED(Client *client);
std::string	ERR_NEEDMOREPARAMS(Client *client, std::string cmd);
std::string	ERR_UNKNOWNCOMMAND(Client *client, std::string cmd);
std::string	ERR_NONICKNAMEGIVEN(Client *client);
std::string	ERR_NICKNAMEINUSE(Client *client, std::string nick);
std::string	ERR_ERRONEUSNICKNAME(Client *client, std::string nick);
std::string	ERR_ERRONEUSUSERNAME(Client *client, std::string cmd);
std::string	ERR_PASSWDMISMATCH(Client *client);
std::string	RPL_WELCOME(Client *client);

#endif /* REPLIES_HPP */
