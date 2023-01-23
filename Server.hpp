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
		std::map<std::string, Channel>	channels;

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
		//aait-oma
		const	std::map<std::string, Channel>& getChannels() const{
			return this->channels;
		};
		bool	channelExists(std::string _channel);
		std::map<std::string, Channel>::iterator getMapElement(const std::string& key);
		void	createChannel(const std::string& key, Channel _channel);
};

#endif /* SERVER_H */
