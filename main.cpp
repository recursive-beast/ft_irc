#include "Server.hpp"
#include <vector>
#include <poll.h>
#include <iostream>
#include "Parser.hpp"

void	handleLine(std::string line, Server *server, Client *client) {
	Parser::parseLine(line, server, client);
	std::cout << "[" << client->addr << ":" << client->port << "]#" << client->sd << ": line: " << line << std::endl;
}

void	handleConnect(Server *server, Client *client) {
	(void)server;
	std::cout << "[" << client->addr << ":" << client->port << "]#" << client->sd << ": connected" << std::endl;
}

void	handleDisconnect(Server *server, Client *client) {
	(void)server;
	std::cout << "[" << client->addr << ":" << client->port << "]#" << client->sd << ": disconnected" << std::endl;
}

int main (int argc, char **argv) {
	Server	*server = NULL;

	try {
		if (argc != 3)
			throw std::runtime_error("Invalid arg count");
		signal(SIGPIPE, SIG_IGN);
		server = new Server(std::stoi(argv[1]), std::string(argv[2]));
		server->onLine = handleLine;
		server->onConnect = handleConnect;
		server->onDisconnect = handleDisconnect;
		Parser::initCmnds();
		server->poll();
		delete server;
		return (0);
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
		delete server;
		return (1);
	}
}

// int main()
// {
// 	std::string	line = "msg target rta fdfdfdfdfdfdfdfdf jhjh hjh jjh jhjh jhjh jh zbi";
// 	line = line.substr(line.find_first_not_of(' '));
// 	for (size_t i = 0; i < 3; i++)
// 	{
// 		line = line.substr(line.find_first_of(' '));
// 		line = line.substr(line.find_first_not_of(' '));
// 	}
// 	std::cout << line << std::endl;
// }
