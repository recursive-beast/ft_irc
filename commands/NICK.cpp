#include "replies.hpp"
#include "commands.hpp"
#include "validation.hpp"

std::string	NICK(Message msg, Server *server, Client *client) {
	std::string	nick;

	if (msg.params.size() < 1)
		return (ERR_NONICKNAMEGIVEN(client));
	nick = msg.params[0];
	if (!isnickname(nick))
		return (ERR_ERRONEUSNICKNAME(client, nick));
	if (server->getClient(nick, false))
		return (ERR_NICKNAMEINUSE(client, nick));
	if (client->registered)
		server->broadcast(NICK_CHANGE(client, nick));
	client->setNickname(nick);
	return (NO_REPLY());
}
