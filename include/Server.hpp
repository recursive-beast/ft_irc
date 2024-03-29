#ifndef SERVER_H
# define SERVER_H

# include "Client.hpp"
# include "Channel.hpp"
# include <string>
# include <map>
# include <poll.h>
# include <vector>
# include <set>

class Server {
	typedef void (*t_line_handler)(std::string, Server *, Client *);
	typedef void (*t_connect_handler)(Server *, Client *);
	typedef void (*t_disconnect_handler)(Server *, Client *);

	friend class Client;
	friend class Channel;

	std::map<int, Client *>				clientsBySD;
	std::map<std::string, Client *>		clientsByNickname;
	std::map<std::string, Channel *>	channels;
	std::vector<pollfd>					pollfds;

	int		accept();
	void	cleanup();

	public:
		const int				port;
		const std::string		password;
		const int				sd;
		t_line_handler			onLine;
		t_connect_handler		onConnect;
		t_disconnect_handler	onDisconnect;

		Server(int port, std::string password);
		~Server();

		Client						*getClient(int sd) const;
		Client						*getClient(std::string nickname) const;
		void						broadcast(std::string s);
		Channel						*createChannel(std::string name, Client *creator);
		Channel						*getChannel(std::string name);
		std::vector<Channel *>		getChannels();
		std::vector<Channel *>		getChannels(std::vector<std::string> names);
		std::vector<Channel *>		getChannels(Client *client);
		std::vector<std::string>	getChannelNames();
		std::vector<std::string>	getChannelNames(Client *client);
		void						poll();
};

#endif /* SERVER_H */
