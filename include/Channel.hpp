#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# define CH_MODE_CREATOR		('O')
# define CH_MODE_OPERATOR		('o')
# define CH_MODE_VOICE			('v') // if m activ gha hada li ayhder and opereter

# define CH_MODE_INVITE_ONLY	('i')
# define CH_MODE_MODERATED		('m') // ta7ed maydwi
# define CH_MODE_NO_OUTSIDE		('n') // ta7ed mayssift mn 3la bera
# define CH_MODE_TOPIC			('t')
# define CH_MODE_KEY			('k')
# define CH_MODE_LIMIT			('l')
# define CH_MODE_SECRET			('s')
# define CH_MODE_PRIVATE		('p')

# include "Client.hpp"
# include <set>
# include <string>
# include <map>
# include <vector>

class Server;

class Channel
{
	std::map<Client *, std::set<char> >	members;
	std::set<char>						modes;
	std::set<std::string>				inviteList;

	friend std::string	MSG_MODE(Client *client, Channel *channel);

	public:
		Server *const		server;
		const std::string	name;
		unsigned int		limit;
		std::string			key;
		std::string			topic;

		Channel(Server *server, std::string name, Client *creator);

		void					broadcast(std::string message);
		void					broadcast(std::string message, Client *except);
		bool					join(Client *client);
		bool					part(Client *client);
		Client					*getMember(std::string nickname);
		std::vector<Client *>	getMembers();
		size_t					getCount();
		bool					isOn(Client *client);
		void					invite(Client *client);
		bool					isInvited(Client *client);
		bool					setMode(char mode);
		bool					setMode(char mode, Client *client);
		bool					hasMode(char mode);
		bool					hasMode(char mode, Client *client);
		bool					unsetMode(char mode);
		bool					unsetMode(char mode, Client *client);
};

#endif /* CHANNEL_HPP */
