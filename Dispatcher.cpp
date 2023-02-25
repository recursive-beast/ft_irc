#include "commands.hpp"
#include "replies.hpp"

std::string	PASS(Message msg, Server *server, Client *client);
std::string	NICK(Message msg, Server *server, Client *client);
std::string	USER(Message msg, Server *server, Client *client);
std::string	PART(Message msg, Server *server, Client *client);
std::string	TOPIC(Message msg, Server *server, Client *client);
std::string	INVITE(Message msg, Server *server, Client *client);
std::string	NAMES(Message msg, Server *server, Client *client);
std::string	LIST(Message msg, Server *server, Client *client);
std::string	KICK(Message msg, Server *server, Client *client);
std::string	JOIN(Message msg, Server *server, Client *client);
std::string	PONG(Message msg, Server *server, Client *client);
std::string	QUIT(Message msg, Server *server, Client *client);
std::string	PRIVMSG(Message msg, Server *server, Client *client);
std::string	NOTICE(Message msg, Server *server, Client *client);
std::string	MODE(Message msg, Server *server, Client *client);
std::string	BOT(Message msg, Server *server, Client *client);

void	Dispatcher::init(std::map<std::string, t_cmd_handler> &handlers) {
	handlers["PASS"] = PASS;
	handlers["NICK"] = NICK;
	handlers["USER"] = USER;
	handlers["PART"] = PART;
	handlers["TOPIC"] = TOPIC;
	handlers["INVITE"] = INVITE;
	handlers["NAMES"] = NAMES;
	handlers["LIST"] = LIST;
	handlers["KICK"] = KICK;
	handlers["JOIN"] = JOIN;
	handlers["PONG"] = PONG;
	handlers["QUIT"] = QUIT;
	handlers["PRIVMSG"] = PRIVMSG;
	handlers["NOTICE"] = NOTICE;
	handlers["MODE"] = MODE;
	handlers["BOT"] = BOT;
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
