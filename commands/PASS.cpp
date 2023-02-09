#include "replies.hpp"
#include "commands.hpp"

std::string	PASS(Message msg, Server *, Client *client) {
	if (client->registered)
		return (ERR_ALREADYREGISTRED(client));
	if (msg.params.size() < 1)
		return (ERR_NEEDMOREPARAMS(client, msg.cmd));
	client->password = msg.params[0];
	return (NO_REPLY());
}
