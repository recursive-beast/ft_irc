#ifndef PARSER_H
# define PARSER_H

# include "Server.hpp"

class Parser {
	public:
		typedef	void (*func)(std::string line, Server *server, Client *client);
		static void	parseLine(std::string line, Server *server, Client *client);
		static void	initCmnds();
		static std::map<std::string, func>	commandes;

	private:

};

bool	checkNickName(std::string nickName);
void	_Registred(Client *client);

#endif /* PARSER_H */