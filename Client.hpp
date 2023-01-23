#ifndef CLIENT_H
# define CLIENT_H

# include <string>
# include <sys/types.h>

# define RECV_BUFFER_SIZE	(512)

class Client {
	private:
		std::string	recv_buffer;
		std::string	send_buffer;

	public:
		// syakoubi part
		const int			sd;
		const int			port;
		const std::string	addr;
		bool				connected;
		std::string			nickname;
		// mmessaoudi part
		std::string			userName;
		std::string			realName;
		std::string			pass;
		bool				registred;
		int					mood;

		Client(int sd, int port, std::string addr);
		~Client();

		std::string	getline();
		bool		hasLine();
		void		write(std::string s);
		ssize_t		recv();
		ssize_t		send();
		void		disconnect();
		// aait-oma
		friend bool	operator==(const Client & lhs, const Client & rhs) {
			return lhs.nickname == rhs.nickname;
		}
};

#endif /* CLIENT_H */
