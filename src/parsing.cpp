#include "IRC.hpp"

void	Server::parseMsg(int fd, std::istringstream &msg)
{
	std::string command;
	std::string messages[] = {"PASS", "USER", "NICK", "PRIVMSG", "JOIN", "PART", "INVITE", "TOPIC", "KICK", "MODE"};
	int i;

	msg >> command;
	for (i = 0 ; i < 10 ; i++)
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
			pass(msg, fd);
			break;
		case (1):
			user(msg, fd);
			break;
		// case (2):
		// 	nick(msg, findClientByFd(fd));
		// 	break;
		case (3):
			privmsg(msg, fd);
			break;
		case (4):
			join(msg, fd);
			break;
		case (5):
			part(msg, fd);
			break ;
		case (6):
			invite(msg, fd);
			break;
		case (7):
			topic(msg, fd);
			break ;
		case (8):
			kick(msg, fd);
			break ;
		case (9):
			mode(msg, fd);
			break ;
		default : 
			clientLog(fd, ERR_CMD_NOT_FND);
	}
}