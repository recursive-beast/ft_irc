#ifndef UTILS_HPP
# define UTILS_HPP

# include <vector>
# include <string>

void						perror_except(const char *s);
std::vector<std::string>	split(std::string s, std::string delimiter);
std::string					join(std::vector<std::string> tokens, std::string delimiter);

#endif /* UTILS_HPP */
