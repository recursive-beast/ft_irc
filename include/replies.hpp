#ifndef REPLIES_HPP
# define REPLIES_HPP

# include <string>

std::string	NO_REPLY();
std::string	ERR_ALREADYREGISTRED();
std::string	ERR_NEEDMOREPARAMS(std::string cmd);
std::string	ERR_UNKNOWNCOMMAND(std::string cmd);

#endif /* REPLIES_HPP */
