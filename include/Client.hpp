#ifndef CLIENT_HPP
#define CLIENT_HPP

# include <string>
# include <sys/types.h>

# define RECV_BUFFER_SIZE	(512)

class Client {
	private:
		std::string	recv_buffer;
		std::string	send_buffer;
		bool		connected;

	public:
		const int			sd;
		const int			port;
		const std::string	addr;
		std::string			nickname;

		Client(int sd, int port, std::string addr);
		~Client();

		std::string	getline();
		bool		hasLine();
		void		write(std::string s);
		ssize_t		recv();
		ssize_t		send();
		void		disconnect();
		bool		isConnected();
};

#endif /* CLIENT_HPP */
