#ifndef UTILS_HPP
# define UTILS_HPP

# include <vector>
# include <string>

void						perror_except(const char *s);
std::vector<std::string>	split(std::string s, std::string delimiter);
std::string					join(std::vector<std::string> tokens, std::string delimiter);

template <typename T>
std::vector<T>				filter(const std::vector<T> &input, bool (*predicate)(const T &)) {
	std::vector<T>	output;
	T				elem;

	for (size_t i = 0; i < input.size(); i++) {
		if (predicate(input[i]))
			output.push_back(input[i]);
	}
    return output;
}

#endif /* UTILS_HPP */
