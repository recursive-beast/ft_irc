#ifndef REPLIES_HPP
# define REPLIES_HPP

# include "Client.hpp"
# include "Channel.hpp"
# include <string>

std::string	NO_REPLY();
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
std::string	MSG_PART(Client *client, Channel *channel, std::string reason = "");
std::string	RPL_TOPIC(Client *client, Channel *channel);
std::string	RPL_NOTOPIC(Client *client, Channel *channel);
std::string	ERR_CHANOPRIVSNEEDED(Client *client, Channel *channel);
std::string	MSG_TOPIC(Client *client, Channel *channel);
std::string	ERR_NOSUCHNICK(Client *client, std::string nickname);
std::string	ERR_USERONCHANNEL(Client *client, Client *user, Channel *channel);
std::string	RPL_INVITING(Client *client, Client *invited, Channel *channel);
std::string	MSG_INVITE(Client *inviting, Client *invited, Channel *channel);
std::string	RPL_NAMREPLY(Client *client, Channel *channel);
std::string	RPL_ENDOFNAMES(Client *client, Channel *channel);
std::string	RPL_LIST(Client *client, Channel *channel);
std::string	RPL_LISTEND(Client *client);
std::string	MSG_KICK(Client *kicker, Client *kicked, Channel *channel, std::string reason = "");
std::string	ERR_USERNOTINCHANNEL(Client *client, Channel *channel, std::string nickname);
std::string	ERR_BADCHANMASK(Client *client, std::string channel);
std::string	ERR_KEYSET(Client *client, Channel *channel);
std::string	ERR_CHANNELISFULL(Client *client, Channel *channel);
std::string	ERR_UNKNOWNMODE(Client *client, Channel *channel, char mode);
std::string	ERR_INVITEONLYCHAN(Client *client, Channel *channel);
std::string	ERR_BANNEDFROMCHAN(Client *client, Channel *channel);
std::string	ERR_BADCHANNELKEY(Client *client, Channel *channel);
std::string	ERR_NOCHANMODES(Client *client, Channel *channel);
std::string	MSG_JOIN(Client *client, Channel *channel);
std::string	MSG_MODE(Client *client, Channel *channel, char mode, char op, std::string param);
std::string	MSG_QUIT(Client *client, std::string reason = "");
std::string	ERR_NORECIPIENT(Client *client, std::string cmd);
std::string	MSG_PRIVMSG(Client *sender, Client *target, std::string msg);
std::string	MSG_PRIVMSG(Client *sender, Channel *target, std::string msg);
std::string	MSG_NOTICE(Client *sender, Client *target, std::string msg);
std::string	MSG_NOTICE(Client *sender, Channel *target, std::string msg);
std::string	ERR_CANNOTSENDTOCHAN(Client *client, Channel *channel);
std::string	ERR_NOTEXTTOSEND(Client *client);
std::string RPL_CHANNELMODEIS(Client *client, Channel *channel);
std::string	ERR_NOPRIVILEGES(Client *client);


#endif /* REPLIES_HPP */
