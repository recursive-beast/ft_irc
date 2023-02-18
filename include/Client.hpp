#ifndef CLIENT_HPP
#define CLIENT_HPP

# include <string>
# include <sys/types.h>

# define RECV_BUFFER_SIZE	(512)

class Server;

class Client {
	std::string	recv_buffer;
	std::string	send_buffer;
	bool		connected;
	std::string	nickname;

	public:
		Server *const		server;
		const int			sd;
		const int			port;
		const std::string	addr;
		bool				registered;
		std::string			password;
		std::string			username;
		std::string			realname;

		Client(Server *server, int sd, int port, std::string addr);
		~Client();

		std::string	getline();
		bool		hasLine();
		void		write(std::string s);
		ssize_t		recv();
		ssize_t		send();
		void		disconnect();
		bool		isConnected() const;
		std::string	getNickname() const;
		bool		setNickname(std::string nickname);
		std::string	getMask();
};

#endif /* CLIENT_HPP */
