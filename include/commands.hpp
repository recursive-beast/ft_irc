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

class Dispatcher
{
	public:
		typedef void (*t_handler)(Message msg, Server *server, Client *client);

		static bool	dispatch(Message msg, Server *server, Client *client);

	private:
		static void	init(std::map<std::string, t_handler> &handlers);
};

#endif /* COMMANDS_HPP */
