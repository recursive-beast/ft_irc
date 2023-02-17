#ifndef UTILS_HPP
# define UTILS_HPP

# include <vector>
# include <string>

void						perror_except(const char *s);
std::vector<std::string>	split(std::string s, std::string delimiter);
std::string					join(std::vector<std::string> tokens, std::string delimiter);
bool						isNotNULL(void *p);

template <typename T, typename P>
std::vector<T>				filter(const std::vector<T> &input, P predicate) {
	std::vector<T>	output;

	for (size_t i = 0; i < input.size(); i++) {
		if (predicate(input[i]))
			output.push_back(input[i]);
	}
    return output;
}

#endif /* UTILS_HPP */
