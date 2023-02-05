#include "commands.hpp"

Message	parseMessage(std::string msg) {
	Message	result;

	if (msg[0] == ':') {
		msg.erase(0, 1);
		result.prefix = msg.substr(0, msg.find_first_of(' '));
		msg.erase(0, msg.find_first_of(' '));
	}
	msg.erase(0, msg.find_first_not_of(' '));
	result.cmd = msg.substr(0, msg.find_first_of(' '));
	msg.erase(0, msg.find_first_of(' '));
	msg.erase(0, msg.find_first_not_of(' '));
	while (msg.length()) {
		if (msg[0] == ':') {
			msg.erase(0, 1);
			result.params.push_back(msg);
			msg.erase(0);
		} else {
			result.params.push_back(msg.substr(0, msg.find_first_of(' ')));
			msg.erase(0, msg.find_first_of(' '));
			msg.erase(0, msg.find_first_not_of(' '));
		}
	}
	return (result);
}
