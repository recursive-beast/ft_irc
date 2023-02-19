#include "replies.hpp"
#include "commands.hpp"
#include "validation.hpp"
#include "utils.hpp"
#include "Channel.hpp"

std::string	QUIT(Message msg, Server *server, Client *client) {
	std::string	reason;

	if (!client->registered)
		return (ERR_NOTREGISTERED(client, msg.cmd));
	client->disconnect();
	if (msg.params.size() > 0)
		reason = msg.params[0];
	server->broadcast(MSG_QUIT(client, reason));
	return (NO_REPLY());
}
