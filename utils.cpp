#include <stdexcept>
#include <errno.h>
#include <string>
#include <cstring>
#include <vector>

void	perror_except(const char *s) {
	throw std::runtime_error(std::string(s) + ": " + std::strerror(errno));
}

std::vector<std::string>	split(std::string s, std::string delimiter) {
    std::vector<std::string>	result;
    size_t						pos = 0;
    std::string					token;

	if (delimiter.empty())
		throw std::invalid_argument("delimiter cannot be an empty string");
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        result.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    result.push_back(s);
    return (result);
}

std::string	join(std::vector<std::string> tokens, std::string delimiter) {
	std::string	result;

	if (tokens.empty())
		return ("");
	result = tokens[0];
	for (size_t i = 1; i < tokens.size(); i++)
		result += delimiter + tokens[i];
	return (result);
}
