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

bool		checkNickName(std::string nickName);
void		_Registred(Client *client);
std::string skipLeadingWhitespaces(const std::string &str);
bool 		startsWithHash(const std::string &str);

#endif /* PARSER_H */