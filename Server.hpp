#ifndef SERVER_H
# define SERVER_H

# include "Client.hpp"
# include <string>
# include <map>
# include <poll.h>
# include <vector>
# include "Channel.hpp"

class Server {
	typedef void (*t_line_handler)(std::string, Server *, Client *);
	typedef void (*t_connect_handler)(Server *, Client *);
	typedef void (*t_disconnect_handler)(Server *, Client *);

	private:
		std::map<int, Client *>			clientsBySD;
		std::map<std::string, Client *>	clientsByNickname;
		std::vector<pollfd>				pollfds;

		int		accept();
		void	cleanupClients();
		//aait-oma part
		std::vector<Channel>			channels;

	public:
		const int				port;
		const std::string		password;
		const int				sd;
		t_line_handler			onLine;
		t_connect_handler		onConnect;
		t_disconnect_handler	onDisconnect;
		Server(int port, std::string password);
		~Server();
		Client	*getClient(int sd);
		Client	*getClient(std::string nickname);
		int		setClientNickname(Client *client, std::string nickname);
		void	poll();
};

#endif /* SERVER_H */
