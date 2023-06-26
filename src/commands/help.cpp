#include "IRC.hpp"

void	Server::help(std::istringstream &content, int fd)
{
	std::string helpMsg;

	if (!checkEmpty(content))
		return (clientLog(fd, ERR_HELP));
	
	helpMsg = "Here are a list of all the available commands:\n \
	-PASS <password> : enter the server password\n \
	-NICK <nickName> : enter your nickname, it will be you ID for the other users\n \
	-USER <userName> <serverName> <hostName> <realName>: those are additional info to identify yourself\n \
	-JOIN <channelName> [<password>] : enter a channel name to join or create one, add a password if needed\n \
	-HELP : display this message\n \
	Channel operators only : \n\
		-INVITE <userName> <channelName> : enter the nickname of the person you want to invite on your channel\n \
		-MODE <channelName> {[+|-]|o|i|t|l|k} [<userLimit>] [<userName>] : change channel's mode: \n \
			+/- l <userLimit> : change or remove user limit\n \
			+/- o <userName> : give or take channel's operator rights\n \
			+/- i : set or remove invite-only mode\n \
			+/- k [<password>] : set or remove password channel\n \
			+/- t : set or remove TOPIC commands members restriction\n \
		-TOPIC [<newTopic>]: change or check the channel's topic\n \
		-KICK <channelName> <nickName> : kick user from channel\n \
	For more details, check RFC 1459...\n";
	return (clientLog(fd, helpMsg));
}