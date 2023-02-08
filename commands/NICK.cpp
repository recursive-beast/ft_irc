#include "replies.hpp"
#include "commands.hpp"
#include "validation.hpp"

std::string	NICK(Message msg, Server *, Client *client) {
	std::string	nick;

	if (msg.params.size() < 1)
		return (ERR_NONICKNAMEGIVEN(client->getNickname()));
	nick = msg.params[0];
	if (!isnickname(nick))
		return (ERR_ERRONEUSNICKNAME(client->getNickname(), nick));
	if (client->setNickname(nick))
		return (ERR_NICKNAMEINUSE(client->getNickname(), nick));
	return (NO_REPLY());
}
