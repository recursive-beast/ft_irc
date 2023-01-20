#include <stdexcept>
#include <errno.h>
#include <string>
#include <cstring>
#include <vector>

void	perror_except(const char *s) {
	throw std::runtime_error(std::string(s) + ": " + std::strerror(errno));
}

std::vector<std::string> split(std::string text, std::string delimiter)
{
	std::string					token;
	std::vector<std::string>	tokens;

	while (text.size()) {
		text.erase(0, text.find_first_not_of(delimiter));
		token = text.substr(0, text.find_first_of(delimiter));
		text.erase(0, text.find_first_of(delimiter));
		if (token.size())
			tokens.push_back(token);
	}
	return (tokens);
}
