#include "commands.hpp"

void	Dispatcher::init(std::map<std::string, t_handler> &handlers) {
	(void)handlers;
}

bool	Dispatcher::dispatch(Message msg, Server *server, Client *client) {
	static std::map<std::string, Dispatcher::t_handler>				handlers;
	static std::map<std::string, Dispatcher::t_handler>::iterator	it;
	static bool														initialized = false;

	if (!initialized) {
		Dispatcher::init(handlers);
		initialized = true;
	}
	it = handlers.find(msg.cmd);
	if (it == handlers.end())
		return (false);
	it->second(msg, server, client);
	return (true);
}
