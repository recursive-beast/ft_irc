#include "replies.hpp"
#include "commands.hpp"
#include "validation.hpp"
#include "utils.hpp"
#include "Channel.hpp"

static std::vector<Channel *>	mapToChannels(std::vector<std::string> names, Server *server) {
	Channel					*channel;
	std::vector<Channel *>	channels;

	for (size_t i = 0; i < names.size(); i++) {
		channel = server->getChannel(names[i]);
		if (channel)
			channels.push_back(channel);
	}
	return (channels);
}

std::string	LIST(Message msg, Server *server, Client *client) {
	std::vector<Channel *>		channels;
	std::vector<std::string>	names;

	if (!client->registered)
		return (ERR_NOTREGISTERED(client, msg.cmd));
	if (msg.params.size() > 0) {
		names = split(msg.params[0], ",");
		names = filter(names, isnotempty);
	}
	if (names.size() == 0)
		channels = server->getChannels();
	else
		channels = mapToChannels(names, server);
	for (size_t i = 0; i < channels.size(); i++)
		client->write(RPL_LIST(client, channels[i]));
	return (RPL_LISTEND(client));
}
