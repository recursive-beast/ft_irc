#include "commands.hpp"
#include "replies.hpp"

void	Dispatcher::init(std::map<std::string, t_cmd_handler> &handlers) {
	handlers["PASS"] = PASS;
	handlers["NICK"] = NICK;
	handlers["USER"] = USER;
	handlers["PART"] = PART;
	handlers["TOPIC"] = TOPIC;
}

bool	Dispatcher::dispatch(Message msg, Server *server, Client *client) {
	static std::map<std::string, t_cmd_handler>				handlers;
	static std::map<std::string, t_cmd_handler>::iterator	it;
	static bool												initialized = false;
	std::string												reply;

	if (!initialized) {
		Dispatcher::init(handlers);
		initialized = true;
	}
	it = handlers.find(msg.cmd);
	if (it == handlers.end())
		return (false);
	reply = it->second(msg, server, client);
	if (reply != NO_REPLY())
		client->write(reply);
	return (true);
}
