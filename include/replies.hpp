#ifndef REPLIES_HPP
# define REPLIES_HPP

# include <string>

std::string	NO_REPLY();
// :<sender> <reply code> <receiver> <message>\r\n
std::string	REPLY(std::string reply_code, std::string receiver, std::string message);
std::string	ERR_ALREADYREGISTRED(std::string receiver);
std::string	ERR_NEEDMOREPARAMS(std::string receiver, std::string cmd);
std::string	ERR_UNKNOWNCOMMAND(std::string receiver, std::string cmd);

#endif /* REPLIES_HPP */
