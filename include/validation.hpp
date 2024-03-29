#ifndef VALIDATION_HPP
# define VALIDATION_HPP

# include <string>
# include <cctype>

typedef	bool	(*t_elem_validator)(const std::string &s);

bool	isnotempty(const std::string &s);
bool	isuser(const std::string &s);
bool	iskey(const std::string &s);
bool	isspecial(const char &c);
bool	istarget(const std::string &s);
bool	ischannel(const std::string &s);
bool	ishostname(const std::string &s);
bool	isshortname(const std::string &s);
bool	isnickname(const std::string &s);
bool	ischanstring(const std::string &s);
bool	islistof(const std::string &s, t_elem_validator validator);

#endif /* VALIDATION_HPP */
