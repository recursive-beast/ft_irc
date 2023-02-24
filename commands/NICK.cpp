#include "replies.hpp"
#include "commands.hpp"
#include "validation.hpp"

std::string	NICK(Message msg, Server *server, Client *client) {
	std::string	nick;

	if (msg.params.size() < 1)
		return (ERR_NONICKNAMEGIVEN(client));
	if (server->password != client->password)
		return (ERR_PASSWDMISMATCH(client));
	nick = msg.params[0];
	if (!isnickname(nick))
		return (ERR_ERRONEUSNICKNAME(client, nick));
	if (server->getClient(nick))
		return (ERR_NICKNAMEINUSE(client, nick));
	if (client->registered)
		server->broadcast(MSG_NICK(client, nick));
	client->setNickname(nick);
	if (!client->registered && !client->username.empty())
	{
		client->registered = true;
		return (RPL_WELCOME(client));
	}
	return (NO_REPLY());
}
