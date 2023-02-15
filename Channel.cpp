#include "Channel.hpp"
#include "Server.hpp"
#include "Client.hpp"

Channel::Channel(Server *server, std::string name, Client *creator): server(server), name(name) {
	std::set<char>	modes;

	modes.insert(CH_MODE_CREATOR);
	modes.insert(CH_MODE_OPERATOR);
	this->members[creator] = modes;
	this->limit = 0;
}

void	Channel::broadcast(std::string message) {
	std::map<Client *, std::set<char> >::iterator	it;

	for (it = this->members.begin(); it != this->members.end(); it++) {
		it->first->write(message);
	}
}

bool	Channel::join(Client *client) {
	if (this->members.count(client))
		return (false);
	this->members[client] = std::set<char>();
	return (true);
}

bool	Channel::part(Client *client) {
	if (this->members.erase(client) == 0)
		return (false);
	if (this->members.empty())
		server->channels.erase(this->name);
	return (true);
}

Client	*Channel::getMember(std::string nickname) {
	std::map<Client *, std::set<char> >::iterator	it;

	for (it = this->members.begin(); it != this->members.end(); it++) {
		if (it->first->getNickname() == nickname)
			return (it->first);
	}
	return (NULL);
}

std::vector<Client *>	Channel::getMembers() {
	std::map<Client *, std::set<char> >::iterator	it;
	std::vector<Client *>							keys;

	for (it = this->members.begin(); it != this->members.end(); it++) {
		keys.push_back(it->first);
	}
	return (keys);
}

bool	Channel::isOn(Client *client) {
	return (this->members.count(client) == 1);
}

void	Channel::invite(Client *client) {
	this->inviteList.insert(client->getNickname());
}

bool	Channel::isInvited(Client *client) {
	return (this->inviteList.count(client->getNickname()) == 1);
}

bool	Channel::setMode(char mode) {
	this->modes.insert(mode);
	return (true);
}

bool	Channel::setMode(char mode, Client *client) {
	std::map<Client *, std::set<char> >::iterator	it;

	it = this->members.find(client);
	if (it == this->members.end())
		return (false);
	it->second.insert(mode);
	return (true);
}

bool	Channel::hasMode(char mode) {
	return (this->modes.count(mode) == 1);
}

bool	Channel::hasMode(char mode, Client *client) {
	std::map<Client *, std::set<char> >::iterator	it;

	it = this->members.find(client);
	if (it == this->members.end())
		return (false);
	return (it->second.count(mode) == 1);
}
