#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "Server.hpp"
# include "Client.hpp"
# include <string>
# include <vector>

struct Message
{
	std::string prefix;
	std::string cmd;
	std::vector<std::string> params;
};

Message	parseMessage(std::string msg);

typedef std::string	(*t_cmd_handler)(Message msg, Server *server, Client *client);

class Dispatcher
{
	public:
		static bool	dispatch(Message msg, Server *server, Client *client);

	private:
		static void	init(std::map<std::string, t_cmd_handler> &handlers);
};

std::string	PASS(Message msg, Server *server, Client *client);
std::string	NICK(Message msg, Server *server, Client *client);
std::string	USER(Message msg, Server *server, Client *client);
std::string	PART(Message msg, Server *server, Client *client);

#endif /* COMMANDS_HPP */
