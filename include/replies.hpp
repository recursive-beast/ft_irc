#ifndef REPLIES_HPP
# define REPLIES_HPP

# include "Client.hpp"
# include "Channel.hpp"
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
std::string	ERR_NOTREGISTERED(Client *client, std::string cmd);
std::string	MSG_NICK(Client *client, std::string newnick);
std::string	ERR_NOSUCHCHANNEL(Client *client, std::string channel);
std::string	ERR_NOTONCHANNEL(Client *client, Channel *channel);
std::string	MSG_PART(Client *client, Channel *channel, std::string message = "");
std::string	RPL_TOPIC(Client *client, Channel *channel);
std::string	RPL_NOTOPIC(Client *client, Channel *channel);
std::string	ERR_CHANOPRIVSNEEDED(Client *client, Channel *channel);
std::string	MSG_TOPIC(Client *client, Channel *channel);
std::string	ERR_NOSUCHNICK(Client *client, std::string nickname);
std::string	ERR_USERONCHANNEL(Client *client, Client *user, Channel *channel);
std::string	RPL_INVITING(Client *client, Client *invited, Channel *channel);
std::string	MSG_INVITE(Client *inviting, Client *invited, Channel *channel);

#endif /* REPLIES_HPP */
