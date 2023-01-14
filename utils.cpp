#include <stdexcept>
#include <errno.h>
#include <string>
#include <cstring>

void	perror_except(const char *s) {
	throw std::runtime_error(std::string(s) + ": " + std::strerror(errno));
}
