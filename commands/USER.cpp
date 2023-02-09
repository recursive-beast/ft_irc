#include "replies.hpp"
#include "commands.hpp"
#include "validation.hpp"

std::string	USER(Message msg, Server *server, Client *client) {
	if (client->registered)
		return (ERR_ALREADYREGISTRED(client->getNickname()));
	if (msg.params.size() < 4 || msg.params[3].length() == 0)
		return (ERR_NEEDMOREPARAMS(client->getNickname(), msg.cmd));
	if (!isuser(msg.params[0]))
		return (ERR_ERRONEUSUSERNAME(client->getNickname(), msg.cmd));
	if (server->password != client->password)
		return (ERR_PASSWDMISMATCH(client->getNickname()));
	client->username = msg.params[0];
	client->realname = msg.params[3];
	client->registered = true;
	return (RPL_WELCOME(client));
}
