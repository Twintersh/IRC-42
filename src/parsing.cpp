#include "IRC.hpp"

void	Server::parseMsg(int fd, std::istringstream &msg)
{
	std::string command;
	std::string messages[] = {"JOIN", "PASS", "NICK", "PRIVMSG", "USER", "PART"};
	int i;

	msg >> command;
	for (i = 0 ; i < 5 ; i++)
	{
		if (command == messages[i])
			break;
	}
	switch (i)
	{
		case (0):
			// Server::join(msg, findClientByFd(fd));
			break;
		case (1):
			Server::pass(msg, fd);
			break;
		// case (2):
		// 	// Server::nick(msg, findClientByFd(fd));
		// 	break;
		// case (3)
		// 	// Server::prvmsg(msg, findClientByFd(fd));
		// 	break;
		case (4):
			Server::user(msg, fd);
			break;
		// case (5)
		default : 
			std::cout << "Command not found" << std::endl;
	}
}