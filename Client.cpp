#include "Client.hpp"
#include "utils.hpp"
#include <vector>
#include <string>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <stdexcept>

Client::Client(int sd, int port, std::string addr): sd(sd), port(port), addr(addr) {
	this->connected = true;
}

std::string	Client::getline() {
	size_t		pos;
	std::string	line;

	pos = this->recv_buffer.find("\r\n");
	if (pos == std::string::npos)
		throw std::runtime_error("no line available");
	line = this->recv_buffer.substr(0, pos);
	this->recv_buffer.erase(0, pos + 2);
	return (line);
}

bool	Client::hasLine() {

	return (this->recv_buffer.find("\r\n") != std::string::npos);
}

void	Client::write(std::string s)
{
	this->send_buffer += s;
}

ssize_t	Client::recv() {
	char		buffer[RECV_BUFFER_SIZE];
	ssize_t		count = 0;

	if (!this->connected)
		throw std::runtime_error("client disconnected");
	count = ::recv(this->sd, buffer, sizeof(buffer), 0);
	if (count > 0)
		this->recv_buffer += std::string(buffer, count);
	return (count);
}

ssize_t	Client::send() {
	ssize_t	count = 0;

	if (!this->connected)
		throw std::runtime_error("client disconnected");
	if (this->send_buffer.size()) {
		count = ::send(this->sd, this->send_buffer.c_str(), this->send_buffer.size(), 0);
		if (count > 0)
			this->send_buffer.erase(0, count);
	}
	return (count);
}

void	Client::disconnect() {
	if (this->connected) {
		close(this->sd);
		this->connected = false;
	}
}

Client::~Client() {
	this->disconnect();
}
