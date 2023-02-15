#ifndef VALIDATION_HPP
# define VALIDATION_HPP

# include <string>
# include <cctype>

bool	isuser(const std::string &s);
bool	iskey(const std::string &s);
bool	isspecial(const char &c);
bool	istargetlist(const std::string &s);
bool	istarget(const std::string &s);
bool	ischannel(const std::string &s);
bool	ishostname(const std::string &s);
bool	isshortname(const std::string &s);
bool	isnickname(const std::string &s);
bool	ischanstring(const std::string &s);

#endif /* VALIDATION_HPP */
