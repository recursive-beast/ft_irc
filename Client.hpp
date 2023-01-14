#ifndef CLIENT_H
# define CLIENT_H

# include <string>
# include <sys/types.h>

# define RECV_BUFFER_SIZE	(4096)

class Client {
	private:
		std::string	recv_buffer;
		std::string	send_buffer;

	public:
		const int			sd;
		const int			port;
		const std::string	addr;
		bool				connected;
		std::string			nickname;

		Client(int sd, int port, std::string addr);
		~Client();

		std::string	getline();
		bool		hasLine();
		void		write(std::string s);
		ssize_t		recv();
		ssize_t		send();
		void		disconnect();
};

#endif /* CLIENT_H */
