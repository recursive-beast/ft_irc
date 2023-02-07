#ifndef CLIENT_HPP
#define CLIENT_HPP

# include <string>
# include <sys/types.h>

# define RECV_BUFFER_SIZE	(512)

class Server;

class Client {
	private:
		std::string	recv_buffer;
		std::string	send_buffer;
		bool		connected;
		std::string	nickname;

	public:
		Server *const		server;
		const int			sd;
		const int			port;
		const std::string	addr;

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
		int			setNickname(std::string nickname);
};

#endif /* CLIENT_HPP */
