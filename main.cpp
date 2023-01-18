#include "Server.hpp"
#include <vector>
#include <poll.h>
#include <iostream>

void	handleLine(std::string line, Server *server, Client *client) {
	(void)server;
	client->write(line + "\n");
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
