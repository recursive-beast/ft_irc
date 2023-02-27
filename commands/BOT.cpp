#include "replies.hpp"
#include "commands.hpp"
#include "validation.hpp"
#include "Channel.hpp"
#include <iostream>

std::string	_displayTimestamp(void)
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer [30];

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	strftime (buffer,30,"%H:%M",timeinfo);
	return (buffer);
}

std::string	BOT(Message msg, Server *, Client *client)
{
	std::map<std::string, std::string>				cmds;
	std::map<std::string, std::string>::iterator	it;

	cmds["PART    :"] = "The PART command causes the user sending the message to be removed \
						from the list of active members for all given channels listed in the parameter string";
	cmds["PRIVMSG :"] = "PRIVMSG is used to send private messages between users, as well as to \
						send messages to channels";
	cmds["MODE    :"] = "The MODE command is provided so that users may query and change the \
   						characteristics of a channel";
	cmds["PASS    :"] = "The PASS command is used to set a 'connection password'";
	cmds["NICK    :"] = "NICK command is used to give user a nickname or change the existing one";
	cmds["USER    :"] = "The USER command is used at the beginning of connection to specify the username";
	cmds["TOPIC   :"] = "The TOPIC command is used to change or view the topic of a channel";
	cmds["INVITE  :"] = "The INVITE command is used to invite a user to a channel";
	cmds["NAMES   :"] = "By using the NAMES command, a user can list all nicknames that are visible to him";
	cmds["LIST    :"] = "The list command is used to list channels and their topics";
	cmds["KICK    :"] = "The KICK command can be used to request the forced removal of a user from a channel";
	cmds["JOIN    :"] = "The JOIN command is used by a user to request to start listening to the specific channel";
	cmds["PONG    :"] = "PONG message is a reply to ping message";
	cmds["NOTICE  :"] = "The NOTICE command is used similarly to PRIVMSG, but no reply is sent to the client";
	cmds["QUIT    :"] = "The SQUIT command is available only to operators";

	it = cmds.begin();

	if (msg.params.size() >= 1 && msg.params[0] == "help")
	{
		while (it != cmds.end())
		{
			client->write(":BOT NOTICE " + client->getNickname() + " :" + it->first + it->second + "\r\n");
			it++;
		}
	}
	else if (msg.params.size() >= 1 && msg.params[0] == "ircDOC")
	{
		client->write(":BOT NOTICE " + client->getNickname() + " :https://www.rfcreader.com/#rfc2812\r\n");
	}
	else if (msg.params.size() >= 1 && msg.params[0] == "time")
	{
		client->write(":BOT NOTICE " + client->getNickname() + " :" + _displayTimestamp() + "\r\n");
	}
	else
		client->write(":BOT NOTICE " + client->getNickname() + " :only these commands are supported as of now: [help, ircDOC, time]\r\n");

	return(NO_REPLY());
}