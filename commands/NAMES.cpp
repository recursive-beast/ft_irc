#include "replies.hpp"
#include "commands.hpp"
#include "validation.hpp"
#include "utils.hpp"
#include "Channel.hpp"

std::string	NAMES(Message msg, Server *server, Client *client) {
	std::vector<Channel *>		channels;
	std::vector<std::string>	names;

	if (!client->registered)
		return (ERR_NOTREGISTERED(client, msg.cmd));
	if (msg.params.size() > 0)
		names = split(msg.params[0], ",");
	if (names.size() == 0)
		channels = server->getChannels();
	else
		channels = filter(server->getChannels(names), isNotNULL);
	for (size_t i = 0; i < channels.size(); i++) {
		client->write(RPL_NAMREPLY(client, channels[i]));
		client->write(RPL_ENDOFNAMES(client, channels[i]));
	}
	return (NO_REPLY());
}
