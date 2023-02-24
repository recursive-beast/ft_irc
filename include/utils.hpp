#ifndef UTILS_HPP
# define UTILS_HPP

# include <vector>
# include <string>

void						perror_except(const char *s);
std::vector<std::string>	split(std::string s, std::string delimiter);
bool						isNotNULL(void *p);
std::string					stoupper(const std::string& s);

template <typename T>
std::string					join(const T &tokens, std::string delimiter = "") {
    std::string					result;
    typename T::const_iterator	it = tokens.cbegin();
    typename T::const_iterator	end = tokens.cend();

    if (it != end) {
        result = *it;
        ++it;
    }
    while (it != end) {
        result += delimiter + *it;
        ++it;
    }
    return result;
}

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
