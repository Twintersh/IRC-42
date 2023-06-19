#include "IRC.hpp"

void	Server::parseMsg(int fd, std::istringstream &msg)
{
	std::string command;
	std::string messages[] = {"PASS", "USER", "NICK", "PRIVMSG", "JOIN", "PART"};
	int i;

	msg >> command;
	for (i = 0 ; i < 5 ; i++)
	{
		if (command == messages[i])
			break;
	}
	if (this->_clients[fd]->getStatus() != registered && i > 1)
	{
		if (this->_clients[fd]->getStatus() == pendingPassword)
			clientLog(fd, ERR_LOGIN);
		else
			clientLog(fd, ERR_REGIS);
		return ;
	}
	switch (i)
	{
		case (0):
			Server::pass(msg, fd);
			break;
		case (1):
			Server::user(msg, fd);
			break;
		// case (2):
		// 	// Server::nick(msg, findClientByFd(fd));
		// 	break;
		// case (3)
		// 	// Server::prvmsg(msg, findClientByFd(fd));
		// 	break;
		case (4):
			Server::join(msg, fd);
			break;
		case (5):
			Server::part(msg, fd);
			break ;
		default : 
			clientLog(fd, ERR_CMD_NOT_FND);
	}
}