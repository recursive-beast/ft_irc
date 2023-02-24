#include "Server.hpp"
#include "commands.hpp"
#include "replies.hpp"
#include <vector>
#include <poll.h>
#include <iostream>
#include <signal.h>

void	handleLine(std::string line, Server *server, Client *client) {
	Message	msg;

	std::cout << "[" << client->addr << ":" << client->port << "]#" << client->sd << ": line: " << line << std::endl;
	msg = parseMessage(line);
	if (msg.cmd.length() && !Dispatcher::dispatch(msg, server, client))
		client->write(ERR_UNKNOWNCOMMAND(client, msg.cmd));
}

void	handleConnect(Server *server, Client *client) {
	(void)server;
	std::cout << "[" << client->addr << ":" << client->port << "]#" << client->sd << ": connected" << std::endl;
}

void	handleDisconnect(Server *server, Client *client) {
	if (client->isCrashed())
		server->broadcast(MSG_QUIT(client, "Connection lost"));
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
		delete server;
		std::cerr << "Error\n" << e.what() << std::endl;
		return (1);
	}
}
