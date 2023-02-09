#include <string>
#include <cctype>
#include "validation.hpp"

bool	isuser(const std::string &s) {
	// US_ASCII characters except NUL, CR, LF, " " and "@"
	return (s.find_first_of("\x00\x0D\x0A @") == std::string::npos);
}

bool	iskey(const std::string &s) {
	if (s.empty() || s.length() > 23)
		return (false);
	for (size_t i = 0; i < s.length(); i++) {
		// 7-bit US_ASCII characters except NUL, CR, LF, FF, h/v TABs, and " "
		if (!((s[i] >= 1 && s[i] <= 5)
			|| (s[i] >= 7 && s[i] <= 8)
			|| s[i] == 0x0C
			|| (s[i] >= 0x0E && s[i] <= 0x1F)
			|| (s[i] >= 0x21 && s[i] <= 0x7F)))
			return (false);
	}
	return (true);
}

bool	isspecial(const char &c) {
	return (c >= '[' && c <= '`') || (c >= '_' && c <= '}');
}

bool	ismsgtarget(const std::string &s) {
	size_t	pos;

	if (s.empty())
		return (false);
	pos = s.find(",");
	if (pos == std::string::npos)
		return (ismsgto(s));
	return (ismsgto(s.substr(0, pos)) && ismsgtarget(s.substr(pos + 1)));
}

bool	ismsgto(const std::string &s) {
	return (ischannel(s) || isnickname(s));
}

bool	ischannel(const std::string &s) {
	if (s.empty() || s[0] != '#')
		return (false);
	return (ischanstring(s.substr(1)));
}

bool	ishostname(const std::string &s) {
	size_t	pos = s.find(".");
	if (pos == std::string::npos)
		return (isshortname(s));
	return (isshortname(s.substr(0, pos)) && ishostname(s.substr(pos + 1)));
}

bool	isshortname(const std::string &s) {
	if (s.empty())
		return (false);
	if (!std::isalpha(s[0]) && !std::isdigit(s[0]))
		return (false);
	for (size_t i = 1; i < s.size(); ++i) {
		if (!std::isalpha(s[i]) && !std::isdigit(s[i]) && s[i] != '-')
			return (false);
	}
	return (true);
}

bool	isnickname(const std::string &s) {
	if (s.empty() || s.size() > 8)
		return (false);
	if (!std::isalpha(s[0]) && !isspecial(s[0]))
		return (false);
	for (size_t i = 1; i < s.size(); ++i) {
		if (!std::isalpha(s[i]) && !std::isdigit(s[i]) && !isspecial(s[i]) && s[i] != '-')
			return (false);
	}
	return (true);
}

bool	ischanstring(const std::string &s) {
	unsigned char	c;

	if (s.empty())
		return (false);
	for (size_t i = 0; i < s.length(); i++) {
		c = s[i];
		if (!((c >= 0x01 && c <= 0x07)
		|| (c >= 0x08 && c <= 0x09)
		|| (c >= 0x0B && c <= 0x0C)
		|| (c >= 0x0E && c <= 0x1F)
		|| (c >= 0x21 && c <= 0x2B)
		|| (c >= 0x2D && c <= 0x39)
		|| (c >= 0x3B && c <= 0xFF)))
			return (false);
	}
	return (true);
}
