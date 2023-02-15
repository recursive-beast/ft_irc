#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
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

Client	*Server::getClient(int sd) const {
	std::map<int, Client *>::const_iterator	it;

	it = this->clientsBySD.find(sd);
	if (it == this->clientsBySD.end())
		return (NULL);
	return (it->second);
}

Client	*Server::getClient(std::string nickname) const {
	std::map<std::string, Client *>::const_iterator	it;

	it = this->clientsByNickname.find(nickname);
	if (it == this->clientsByNickname.end())
		return (NULL);
	return (it->second);
}

int	Server::accept() {
	int			client_sd;
	Client		*client;
	sockaddr_in	addr;
	socklen_t	len;

	len = sizeof(addr);
	client_sd = ::accept(this->sd, (sockaddr *)&addr, &len);
	if (client_sd != -1) {
		client = new Client(this, client_sd, ntohs(addr.sin_port), inet_ntoa(addr.sin_addr));
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
		if (client->isConnected())
			continue;
		this->clientsByNickname.erase(client->getNickname());
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
			if (!client->isConnected())
				continue;
			if (revents & (POLLERR | POLLHUP)) {
				client->disconnect();
				continue;
			}
			if ((revents & POLLIN) && client->recv() <= 0) {
				client->disconnect();
				continue;
			}
			while (client->isConnected() && this->onLine && client->hasLine())
				this->onLine(client->getline(), this, client);
			if (client->isConnected() && (revents & POLLOUT) && client->send() < 0)
				client->disconnect();
		}
		this->cleanupClients();
	}
}

void	Server::broadcast(std::string s) {
	std::map<std::string, Client *>::iterator it;

	for (it = this->clientsByNickname.begin(); it != this->clientsByNickname.end(); it++) {
		if (it->second->registered)
			it->second->write(s);
	}
}

Channel	*Server::createChannel(std::string name, Client *creator) {
	if (this->channels.count(name))
		return (NULL);
	this->channels[name] = new Channel(this, name, creator);
	return (this->channels[name]);
}

Channel	*Server::getChannel(std::string name) {
	if (this->channels.count(name))
		return (this->channels[name]);
	return (NULL);
}

std::vector<Channel *>	Server::getChannels() {
	std::vector<Channel *>	list;
	std::map<std::string, Channel *>::iterator it;

	for (it = this->channels.begin(); it != this->channels.end(); it++) {
		list.push_back(it->second);
	}
	return (list);
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
