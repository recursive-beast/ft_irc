#include "Server.hpp"
#include "Client.hpp"
#include "utils.hpp"
#include <sys/socket.h>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <poll.h>
#include <errno.h>
#include <cstring>
#include <stdexcept>
#include <signal.h>

Server::Server(int port, std::string password): port(port), password(password), sd(socket(PF_INET, SOCK_STREAM, 0)) {
	sockaddr_in addr;

	this->onLine = NULL;
	this->onConnect = NULL;
	this->onDisconnect = NULL;
	if (this->sd == -1)
		perror_except("socket");
	if (fcntl(this->sd, F_SETFL, O_NONBLOCK) == -1)
		perror_except("fcntl");
	int on = 1;
	if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (int *)&on, sizeof(on)))
		perror_except("setsockopt");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	memset(addr.sin_zero, 0, sizeof(addr.sin_zero));
	if (bind(sd, (sockaddr *)&addr, sizeof(addr)))
		perror_except("bind");
	if (listen(sd, 50))
		perror_except("listen");
	this->pollfds.push_back((pollfd){
		.fd = this->sd,
		.events = POLLIN | POLLOUT,
		.revents = 0
	});
}

Client	*Server::getClient(int sd) {
	std::map<int, Client *>::iterator	it;

	it = this->clientsBySD.find(sd);
	if (it == this->clientsBySD.end())
		return (NULL);
	return (it->second);
}

Client	*Server::getClient(std::string nickname) {
	std::map<std::string, Client *>::iterator	it;

	it = this->clientsByNickname.find(nickname);
	if (it == this->clientsByNickname.end())
		return (NULL);
	return (it->second);
}

int	Server::setClientNickname(Client *client, std::string nickname) {
	if (nickname.length() == 0)
		throw std::runtime_error("nickname should not be empty");
	if (this->getClient(nickname))
		return (-1);
	this->clientsByNickname.erase(client->nickname);
	this->clientsByNickname[nickname] = client;
	client->nickname = nickname;
	return (0);
}

int	Server::accept() {
	int			client_sd;
	Client		*client;
	sockaddr_in	addr;
	socklen_t	len;

	len = sizeof(addr);
	client_sd = ::accept(this->sd, (sockaddr *)&addr, &len);
	if (client_sd != -1) {
		client = new Client(client_sd, ntohs(addr.sin_port), inet_ntoa(addr.sin_addr));
		this->clientsBySD[client_sd] = client;
		this->pollfds.push_back((pollfd){
			.fd = client_sd,
			.events = POLLIN | POLLOUT,
			.revents = 0
		});
		if (this->onConnect)
			this->onConnect(this, client);
	}
	return (client_sd);
}

void	Server::cleanupClients() {
	Client	*client;

	for (size_t i = 1; i < this->pollfds.size(); i++)
	{
		client = this->getClient(this->pollfds[i].fd);
		if (client->connected)
			continue;
		this->clientsByNickname.erase(client->nickname);
		this->clientsBySD.erase(client->sd);
		this->pollfds.erase(this->pollfds.begin() + i);
		if (this->onDisconnect)
			this->onDisconnect(this, client);
		delete client;
		i--;
	}
}

void	Server::poll() {
	int		count;
	Client	*client;
	short	revents;

	while (true) {
		count = ::poll(this->pollfds.data(), this->pollfds.size(), -1);
		if (count == 0)
			continue;
		if (count == -1)
			perror_except("poll");
		if ((this->pollfds[0].revents & POLLIN) && this->accept() == -1)
			perror("accept");
		for (size_t i = 1; i < this->pollfds.size(); i++) {
			client = this->getClient(this->pollfds[i].fd);
			revents = this->pollfds[i].revents;
			if (!client->connected)
				continue;
			if (revents & (POLLERR | POLLHUP)) {
				client->disconnect();
				continue;
			}
			if ((revents & POLLIN) && client->recv() <= 0) {
				client->disconnect();
				continue;
			}
			while (client->connected && this->onLine && client->hasLine())
				this->onLine(client->getline(), this, client);
			if (client->connected && (revents & POLLOUT) && client->send() < 0)
				client->disconnect();
		}
		this->cleanupClients();
	}
}

Server::~Server() {
	std::map<int, Client *>::iterator it;

	for (it = this->clientsBySD.begin(); it != this->clientsBySD.end(); it++) {
		if (this->onDisconnect)
			this->onDisconnect(this, it->second);
		delete it->second;
	}
	close(this->sd);
}
