#include "replies.hpp"
#include "commands.hpp"
#include "validation.hpp"
#include "Channel.hpp"
#include <string>

std::string WHOIS(Message msg, Server *server, Client *client) {
	Client	*target;

	if (!client->registered)
		return (ERR_NOTREGISTERED(client, msg.cmd));
	if (msg.params.size() < 1)
		return (ERR_NEEDMOREPARAMS(client, msg.cmd));
	target = server->getClient(msg.params[0]);
	if (!target)
		return (ERR_NOSUCHNICK(client, msg.params[0]));
	client->write(RPL_WHOISUSER(client, target));
	client->write(RPL_WHOISSERVER(client, target));
	return (RPL_ENDOFWHOIS(client, target));
}
